# Native overlay code, included by CMakeLists.txt
# after the mml and harness targets exist.
#
# Every overlay target in tools/overlays.txt (stages r3_stXX at 0x80100000, weapons r3_shlXX at
# 0x800D8800, r3_sup at 0x801D8000) is one module: the C files its matching link uses (read from
# build/<t>/<t>.ld; the shared src/stage_common files are compiled into each stage that links
# them, with that stage's addresses). Per file: preprocess and rewrite inline MIPS like the game
# sources, compile to assembly. Per module: tools/ovl_rewrite.py renames the native functions
# (port_ovl_<module>_<name>), sets every other overlay symbol to its retail address from the
# module's ELF, and assembles. tools/gen_ovl_table.py then writes the table that
# port_overlay_native_find() (runtime/overlay.c) uses: retail address, size, hash of the retail
# bytes, native function. Functions still in assembly stay interpreted.
#
# Needs the matching overlay builds (build/r3_*/r3_*.elf and .ld: `make overlays`); a module
# without them is skipped with a warning.

set(OVL_GEN ${GEN}/ovl)

# Parked drafts (-DNON_MATCHING) left interpreted, MODULE:NAME (one module) or NAME (every stage
# that links the shared stage file). The other drafts run natively: their comments say the
# difference from retail is register allocation,
# scheduling, block layout, or an equivalent form (a load's extension that a narrower store or
# cast discards). Left here:
# - no comment saying what differs: the draft's accuracy is unknown;
# - "3 words still differ (work stopped mid-function)": r3_st08 func_801018CC.
set(PORT_OVERLAY_EXCLUDE
    r3_st02:func_80100A28 r3_st02:func_8010592C
    r3_st05:func_8011CF8C r3_st05:func_80120434
    r3_st07:func_80102590 r3_st15:func_801003A0 r3_st16:func_801003D8
    r3_st18:func_8010072C r3_st1c:func_801034C8
    r3_st1e:func_8010011C
    r3_st08:func_801018CC)

# The game flags, plus: no inlining and no interprocedural assumptions between functions (a
# direct call may be redirected to interpreted MIPS code, and a native function must behave on
# its own exactly as its retail bytes do), no sibling calls (every return passes a `ret`, where
# ovl_rewrite.py extends narrow results), and no hot/cold splitting (one body per function).
set(OVL_CFLAGS ${GAME_CFLAGS} -fno-asynchronous-unwind-tables -fno-inline -fno-partial-inlining
    -fno-ipa-cp -fno-ipa-sra -fno-ipa-pure-const -fno-ipa-modref -fno-ipa-ra -fno-ipa-icf
    -fno-ipa-vrp -fno-ipa-bit-cp -fno-ipa-stack-alignment -fno-ipa-reference-addressable
    -fno-optimize-sibling-calls -fno-reorder-blocks-and-partition)

set(OVL_OBJECTS)
set(OVL_JSON)
file(STRINGS ${REPO}/tools/overlays.txt ovl_lines REGEX "^r3_")
foreach(line ${ovl_lines})
    string(REGEX MATCH "^[a-z0-9_]+" mod "${line}")
    set(elf ${REPO}/build/${mod}/${mod}.elf)
    set(ld ${REPO}/build/${mod}/${mod}.ld)
    if(NOT EXISTS ${elf} OR NOT EXISTS ${ld})
        message(WARNING "overlays: no ${elf} or ${ld} (make overlays): ${mod} stays interpreted")
        continue()
    endif()
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${ld})
    file(STRINGS ${ld} ld_lines REGEX "build/${mod}/src/.*\\.o\\(")
    set(srcs)
    foreach(l ${ld_lines})
        string(REGEX MATCH "build/${mod}/(src/[^ ]*)\\.o\\(" _ "${l}")
        list(APPEND srcs ${REPO}/${CMAKE_MATCH_1}.c)
    endforeach()
    list(REMOVE_DUPLICATES srcs)

    set(dir ${OVL_GEN}/${mod})
    file(MAKE_DIRECTORY ${dir})
    set(inc)
    if(EXISTS ${REPO}/include/${mod})
        set(inc -I${REPO}/include/${mod})
    endif()
    set(cppflags -DPORT -DNON_MATCHING -Ulinux -Uunix -Ui386 "-DTARGET_ASM=\"asm/${mod}\""
        -include ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
        -I${CMAKE_CURRENT_SOURCE_DIR}/include ${inc} -I${REPO}/include/rock_neo.exe -I${REPO}/include)
    set(asm_files)
    set(objs)
    foreach(src ${srcs})
        get_filename_component(name ${src} NAME_WE)
        set(s ${dir}/${name}.s)
        add_custom_command(
            OUTPUT ${s}
            COMMAND ${CMAKE_C_COMPILER} ${cppflags} ${M32} -std=gnu89 -E ${src} -o ${dir}/${name}.i
                    -MD -MF ${dir}/${name}.d -MT ${s}
            COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/tools/asm_rewrite.py
                    ${dir}/${name}.i ${dir}/${name}.port.c
            COMMAND ${CMAKE_C_COMPILER} ${OVL_CFLAGS} -fpreprocessed -aux-info ${dir}/${name}.aux
                    -S ${dir}/${name}.port.c -o ${s}
            DEPENDS ${src} ${CMAKE_CURRENT_SOURCE_DIR}/tools/asm_rewrite.py
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
            DEPFILE ${dir}/${name}.d
            COMMENT "Compiling ${mod}: ${name}.c"
            VERBATIM)
        list(APPEND asm_files ${s})
        list(APPEND objs ${dir}/${name}.ovl.o)
    endforeach()
    add_custom_command(
        OUTPUT ${dir}/${mod}.json ${objs}
        COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/tools/ovl_rewrite.py
                --module ${mod} --elf ${elf} --main-elf ${PORT_RETAIL_ELF} --out-dir ${dir}
                --json ${dir}/${mod}.json --exclude ${PORT_OVERLAY_EXCLUDE}
                "--cc=${CMAKE_C_COMPILER} ${M32}" --files ${asm_files}
        DEPENDS ${asm_files} ${elf} ${PORT_RETAIL_ELF}
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/ovl_rewrite.py
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/ovl_elf.py
        COMMENT "Linking overlay module ${mod} to retail addresses"
        VERBATIM)
    list(APPEND OVL_OBJECTS ${objs})
    list(APPEND OVL_JSON ${dir}/${mod}.json)
endforeach()

if(OVL_JSON)
    add_custom_command(
        OUTPUT ${GEN}/ovl_table.c ${GEN}/ovl_report.txt
        COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_ovl_table.py
                --out ${GEN}/ovl_table.c --report ${GEN}/ovl_report.txt
                --retail-ld ${GEN}/retail.ld ${OVL_JSON}
        DEPENDS ${OVL_JSON} ${GEN}/retail.ld ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_ovl_table.py
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/ovl_elf.py
        COMMENT "Generating the native overlay table"
        VERBATIM)
    set_source_files_properties(${OVL_OBJECTS} PROPERTIES EXTERNAL_OBJECT TRUE GENERATED TRUE)
    foreach(target mml harness)
        target_sources(${target} PRIVATE ${GEN}/ovl_table.c ${OVL_OBJECTS})
    endforeach()
endif()
