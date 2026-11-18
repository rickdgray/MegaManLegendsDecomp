# The boot shim, natively: `mml_boot` runs SLUS_006.03's
# C (src/slus_006.03/main.c, all of it) on the same runtime as the game: the Capcom logo movie
# (libpress on the interpreter, software MDEC), "now loading", then LoadExec, which runs `mml`.
# Included by CMakeLists.txt; placed against the shim's matching build like the game is against
# ROCK_NEO.EXE's.

set(PORT_SHIM_ELF ${REPO}/build/slus_006.03/slus_006.03.elf CACHE FILEPATH
    "The boot shim's matching ELF (./tools/build.sh slus_006.03)")
set(PORT_SHIM_EXE ${REPO}/disc/extracted/SLUS_006.03 CACHE FILEPATH
    "The owner's SLUS_006.03, read at run time (make extract)")

if(NOT EXISTS ${PORT_SHIM_ELF})
    message(WARNING "No ${PORT_SHIM_ELF}: build slus_006.03 first; mml_boot skipped")
    return()
endif()

set(SHIM_GEN ${GEN}/shim)
file(MAKE_DIRECTORY ${SHIM_GEN})
set(SHIM_CPPFLAGS -DPORT -DPORT_SHIM -DNON_MATCHING -Dmain=psx_main -Ulinux -Uunix -Ui386
    -include ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
    -I${CMAKE_CURRENT_SOURCE_DIR}/include -I${REPO}/include/slus_006.03 -I${REPO}/include)

set(SHIM_SRC ${REPO}/src/slus_006.03/main.c)
set(SHIM_I ${SHIM_GEN}/main.i)
set(SHIM_C ${SHIM_GEN}/main.port.c)
add_custom_command(
    OUTPUT ${SHIM_C}
    COMMAND ${CMAKE_C_COMPILER} ${SHIM_CPPFLAGS} ${M32} -std=gnu89 -E ${SHIM_SRC} -o ${SHIM_I}
    COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/tools/asm_rewrite.py ${SHIM_I} ${SHIM_C}
    DEPENDS ${SHIM_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/tools/asm_rewrite.py
            ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
    IMPLICIT_DEPENDS C ${SHIM_SRC}
    COMMENT "Preparing the boot shim's main.c for the native build"
    VERBATIM)
set_source_files_properties(${SHIM_C} PROPERTIES COMPILE_OPTIONS "-fpreprocessed")

add_library(shim_game OBJECT ${SHIM_C})
target_compile_options(shim_game PRIVATE ${GAME_CFLAGS})

# The native PsyQ libraries again, for the shim's addresses and libgpu's state in its data.
set(SHIM_NATIVE_SOURCES psyq/libgpu.c psyq/libetc.c psyq/libapi.c psyq/libcd.c)
add_library(shim_native OBJECT ${SHIM_NATIVE_SOURCES})
target_include_directories(shim_native PRIVATE runtime)
target_compile_definitions(shim_native PRIVATE PORT_SHIM PORT_GPU_STATE=0x80048090u)
target_compile_options(shim_native PRIVATE ${M32} -fno-pic -fno-builtin ${RT_WARN} ${PLACE_CFLAGS})

add_library(shim_emulated OBJECT psyq/shim_psyq.c)
target_include_directories(shim_emulated PRIVATE runtime)
target_compile_options(shim_emulated PRIVATE ${M32} -fno-pic -fno-builtin ${RT_WARN})

add_library(shim_main OBJECT runtime/host_main.c)
target_compile_options(shim_main PRIVATE ${M32} -fno-pic ${RT_WARN})
target_compile_definitions(shim_main PRIVATE PORT_SHIM PORT_DEFAULT_EXE="${PORT_SHIM_EXE}"
                           PORT_DEFAULT_DISC="${PORT_DISC_IMAGE}")
target_include_directories(shim_main PRIVATE runtime mods)

set(SHIM_PLACED ${SHIM_GEN}/placed/main.port.c.o)
foreach(src ${SHIM_NATIVE_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    list(APPEND SHIM_PLACED ${SHIM_GEN}/placed/${name}.c.o)
endforeach()
add_custom_command(
    OUTPUT ${SHIM_PLACED} ${SHIM_GEN}/stubs.c ${SHIM_GEN}/retail.ld ${SHIM_GEN}/link_report.txt
    COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_link.py
            --elf ${PORT_SHIM_ELF} --out-dir ${SHIM_GEN}/placed
            --stubs ${SHIM_GEN}/stubs.c --ld ${SHIM_GEN}/retail.ld
            --report ${SHIM_GEN}/link_report.txt
            --place $<TARGET_OBJECTS:shim_game> $<TARGET_OBJECTS:shim_native>
            --scan $<TARGET_OBJECTS:shim_emulated> $<TARGET_OBJECTS:shim_main>
            --defined $<TARGET_FILE:port_rt32>
    DEPENDS shim_game shim_native shim_emulated shim_main port_rt32 ${PORT_SHIM_ELF}
            ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_link.py
            $<TARGET_OBJECTS:shim_game> $<TARGET_OBJECTS:shim_native>
    COMMENT "Placing the boot shim at retail addresses"
    COMMAND_EXPAND_LISTS
    VERBATIM)
set_source_files_properties(${SHIM_PLACED} PROPERTIES EXTERNAL_OBJECT TRUE GENERATED TRUE)

add_executable(mml_boot ${SHIM_GEN}/stubs.c ${SHIM_PLACED} $<TARGET_OBJECTS:shim_emulated>
               $<TARGET_OBJECTS:shim_main>)
target_compile_options(mml_boot PRIVATE ${M32} -fno-pic -w)
target_include_directories(mml_boot PRIVATE runtime)
target_link_libraries(mml_boot PRIVATE port_rt32)
target_link_options(mml_boot PRIVATE -Wl,-T,${SHIM_GEN}/retail.ld)
set_property(TARGET mml_boot APPEND PROPERTY LINK_DEPENDS ${SHIM_GEN}/retail.ld)
add_dependencies(mml_boot mml) # LoadExec runs it
