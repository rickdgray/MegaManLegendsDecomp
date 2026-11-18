# Included only by the 64-bit AOT build. The game-facing C ABI remains ILP32.
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "PORT_BOOT64 needs a 64-bit host compiler")
endif()

find_program(PORT_WASM_CLANG NAMES clang REQUIRED)
find_program(PORT_WASM_LD NAMES wasm-ld REQUIRED)
find_program(PORT_WASM2C NAMES wasm2c REQUIRED)
find_path(PORT_WABT_INCLUDE wasm-rt.h REQUIRED)
find_path(PORT_WABT_RUNTIME wasm-rt-impl.c PATH_SUFFIXES wabt/wasm2c
    PATHS /usr/share /usr/local/share REQUIRED)

set(PORT_SHIM_ELF ${REPO}/build/slus_006.03/slus_006.03.elf CACHE FILEPATH
    "Matching boot shim ELF")
set(PORT_SHIM_EXE ${REPO}/disc/extracted/SLUS_006.03 CACHE FILEPATH
    "The owner's boot shim PS-X EXE")
set(PORT_DISC_IMAGE ${REPO}/disc/image CACHE PATH
    "The owner's disc image as a cue file or a directory holding one")
if(NOT EXISTS "${PORT_SHIM_ELF}")
    message(FATAL_ERROR "Build the matching boot shim or set PORT_SHIM_ELF")
endif()

set(SHIM_SOURCE ${REPO}/src/slus_006.03/main.c)
set(SHIM_IR ${GEN}/shim.ll)
set(SHIM_BOUND ${GEN}/shim.bound.ll)
set(SHIM_ADDR ${GEN}/shim_addresses.h)
# Put both stacks above the PS1's 2 MiB RAM, away from retail data and movie buffers.
math(EXPR SHIM_STACK_BASE "0x80200000")
math(EXPR SHIM_MEMORY "0x80420000")
set(SHIM_WASM_OBJ ${GEN}/shim.wasm.o)
set(SHIM_WASM ${GEN}/shim.wasm)
set(SHIM_C ${GEN}/shim.c)
set(SHIM_H ${GEN}/shim.h)
add_custom_command(
    OUTPUT ${SHIM_IR}
    COMMAND ${PORT_WASM_CLANG} --target=wasm32-unknown-unknown -std=gnu89
            -DPORT -DPORT_SHIM -DNON_MATCHING -Dmain=psx_main -ffreestanding
            -fno-strict-aliasing -fwrapv -fno-delete-null-pointer-checks
            -ftrivial-auto-var-init=zero -O0 -Xclang -disable-O0-optnone -S -emit-llvm
            -include ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
            -I${REPO}/include/slus_006.03 -I${REPO}/include
            -MMD -MF ${SHIM_IR}.d ${SHIM_SOURCE} -o ${SHIM_IR}
    DEPENDS ${SHIM_SOURCE}
    DEPFILE ${SHIM_IR}.d
    VERBATIM)
add_custom_command(
    OUTPUT ${SHIM_BOUND} ${SHIM_ADDR}
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/tools
            $<TARGET_FILE:Python3::Interpreter> ${CMAKE_CURRENT_SOURCE_DIR}/aot/bind_retail.py
            ${PORT_SHIM_ELF} ${SHIM_IR} ${SHIM_BOUND} ${SHIM_ADDR}
    DEPENDS ${SHIM_IR} ${PORT_SHIM_ELF} aot/bind_retail.py aot/game_dispatch.py tools/asm_rewrite.py tools/gen_link.py
    VERBATIM)
add_custom_command(
    OUTPUT ${SHIM_WASM}
    BYPRODUCTS ${SHIM_WASM_OBJ}
    COMMAND ${PORT_WASM_CLANG} --target=wasm32-unknown-unknown -Oz -c ${SHIM_BOUND} -o ${SHIM_WASM_OBJ}
    COMMAND ${PORT_WASM_LD} --no-entry --export=Vsync_handler --export=Pad_update_all
            --export=Cd_read_sync2 --export=Cd_cmd_set_movie --export=Intro_task
            --export=Cd_cmd_exec --export=Intro_init --export=psx_main
            --export=Cd_sync_cb --export=Movie_sector_cb --export=Movie_dct_out_callback
            --no-stack-first --global-base=${SHIM_STACK_BASE} -z stack-size=65536
            --initial-memory=${SHIM_MEMORY} --max-memory=${SHIM_MEMORY}
            ${SHIM_WASM_OBJ} -o ${SHIM_WASM}
    DEPENDS ${SHIM_BOUND}
    VERBATIM)
add_custom_command(
    OUTPUT ${SHIM_C} ${SHIM_H}
    COMMAND ${PORT_WASM2C} ${SHIM_WASM} -n shim -o ${SHIM_C}
    DEPENDS ${SHIM_WASM}
    VERBATIM)

add_library(port_boot64 STATIC aot/mips_memory.c aot/shim_host.c
    runtime/mips_cpu.c runtime/gte.c runtime/gpu.c runtime/mdec.c runtime/spu.c runtime/psx_io.c
    runtime/psx_exe.c runtime/mips_asm.c
    runtime/port_game.c runtime/port_audio.c runtime/port_script.c runtime/port_config.c
    runtime/port_remote.c runtime/port_overlay.c runtime/pad.c runtime/memcard.c
    psyq/libgpu.c psyq/libetc.c psyq/libcd.c psyq/libapi.c psyq/libgte.c
    ${SHIM_C} ${SHIM_H} ${SHIM_ADDR}
    ${PORT_WABT_RUNTIME}/wasm-rt-impl.c ${PORT_WABT_RUNTIME}/wasm-rt-mem-impl.c)
target_compile_features(port_boot64 PUBLIC c_std_11)
target_include_directories(port_boot64 PUBLIC runtime aot ${GEN} ${PORT_WABT_INCLUDE}
    PRIVATE mods ${PORT_WABT_RUNTIME})
target_compile_definitions(port_boot64 PRIVATE PORT_AOT_MIPS=1 PORT_AOT_STACK_TOP=${SHIM_MEMORY}
    PORT_SHIM PORT_BOOT_SHIM_ONLY PORT_GPU_STATE=0x80048090u PUBLIC WASM_RT_MEMCHECK_BOUNDS_CHECK=1)
target_link_libraries(port_boot64 PUBLIC m)

# A window, sound and gamepads through SDL3 (mml_game64 --window). Without SDL3 the build stays
# headless.
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(SDL3_64 IMPORTED_TARGET sdl3)
endif()
if(SDL3_64_FOUND)
    target_sources(port_boot64 PRIVATE runtime/platform_sdl.c)
    target_compile_definitions(port_boot64 PUBLIC PORT_HAVE_SDL)
    target_link_libraries(port_boot64 PUBLIC PkgConfig::SDL3_64)
else()
    message(STATUS "SDL3 not found: mml_game64 runs headless only")
endif()

add_executable(boot64_check aot/boot64_check.c)
target_link_libraries(boot64_check PRIVATE port_boot64)
add_executable(mml_boot64 aot/boot_main.c)
target_link_libraries(mml_boot64 PRIVATE port_boot64)
target_compile_definitions(mml_boot64 PRIVATE PORT_DEFAULT_EXE="${PORT_SHIM_EXE}"
    PORT_DEFAULT_DISC="${PORT_DISC_IMAGE}")

enable_testing()
add_test(NAME boot64_check COMMAND boot64_check ${PORT_SHIM_EXE})
set_tests_properties(boot64_check PROPERTIES TIMEOUT 15)
add_test(NAME boot64_movie COMMAND mml_boot64)
set_tests_properties(boot64_movie PROPERTIES TIMEOUT 30
    PASS_REGULAR_EXPRESSION "boot shim reached LoadExec.*452 vblanks")

# Prepare the base game for the AOT linker. These modules preserve the wasm32 ABI
# and are compiled separately so retail definitions can be bound per translation unit.
file(GLOB AOT_GAME_SOURCES CONFIGURE_DEPENDS "${REPO}/src/rock_neo.exe/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/*.c")
set(PORT_RETAIL_ELF ${REPO}/build/rock_neo.exe/rock_neo.exe.elf CACHE FILEPATH
    "Matching game ELF for the game64_objects target")
function(game64_compile_objects output dir elf overlay)
    file(MAKE_DIRECTORY "${dir}")
    set(overrides -Dmain=psx_main)
    set(binding_args)
    set(elf_deps "${elf}")
    if(overlay)
        set(overrides "-DTARGET_ASM=\"asm/${overlay}\"" "-I${REPO}/include/${overlay}")
        set(binding_args --main-elf "${PORT_RETAIL_ELF}")
        list(APPEND elf_deps "${PORT_RETAIL_ELF}")
    endif()
    set(objects)
    foreach(src IN LISTS ARGN)
        get_filename_component(name "${src}" NAME_WE)
        set(preprocessed "${dir}/${name}.i")
        set(rewritten "${dir}/${name}.c")
        set(ir "${dir}/${name}.ll")
        set(bound "${dir}/${name}.bound.ll")
        set(object "${dir}/${name}.wasm.o")
        add_custom_command(
            OUTPUT "${ir}"
            BYPRODUCTS "${preprocessed}" "${rewritten}"
            COMMAND ${PORT_WASM_CLANG} --target=wasm32-unknown-unknown -std=gnu89
                    -DPORT -DNON_MATCHING ${overrides} -ffreestanding
                    -include ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
                    -I${REPO}/include/rock_neo.exe -I${REPO}/include
                    -E -MMD -MF "${ir}.d" -MT "${ir}" "${src}" -o "${preprocessed}"
            COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/tools/asm_rewrite.py"
                    "${preprocessed}" "${rewritten}"
            COMMAND ${PORT_WASM_CLANG} --target=wasm32-unknown-unknown -std=gnu89 -ffreestanding
                    -fno-strict-aliasing -fwrapv -fno-delete-null-pointer-checks
                    -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-deprecated-non-prototype
                    -ftrivial-auto-var-init=zero -O0 -Xclang -disable-O0-optnone -S -emit-llvm "${rewritten}" -o "${ir}"
            DEPENDS "${src}" tools/asm_rewrite.py
            DEPFILE "${ir}.d"
            COMMENT "Preparing ${name}.c for the 64-bit game build"
            VERBATIM)
        add_custom_command(
            OUTPUT "${bound}" "${object}"
            COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/tools
                    $<TARGET_FILE:Python3::Interpreter> ${CMAKE_CURRENT_SOURCE_DIR}/aot/bind_retail.py
                    --game ${binding_args} "${elf}" "${ir}" "${bound}"
            COMMAND ${PORT_WASM_CLANG} --target=wasm32-unknown-unknown -O2 -c "${bound}" -o "${object}"
            DEPENDS "${ir}" ${elf_deps} aot/bind_retail.py aot/game_dispatch.py
                    tools/asm_rewrite.py tools/gen_link.py
            VERBATIM)
        list(APPEND objects "${object}")
    endforeach()
    set(${output} "${objects}" PARENT_SCOPE)
endfunction()

game64_compile_objects(AOT_GAME_OBJECTS "${GEN}/game" "${PORT_RETAIL_ELF}" "" ${AOT_GAME_SOURCES})
add_custom_target(game64_objects DEPENDS ${AOT_GAME_OBJECTS})

# Translate the linked base-game module to native host code. Keep every compiled
# function available for the retail-address dispatch table and leave PsyQ as imports.
set(AOT_GAME_WASM "${GEN}/game/rock_neo.wasm")
set(AOT_GAME_C "${GEN}/game/rock_neo.c")
set(AOT_GAME_H "${GEN}/game/rock_neo.h")
# Keep generated static data and the guest C stack beyond the MIPS stack reservation.
math(EXPR AOT_GAME_MEMORY "${SHIM_MEMORY} + 0xA00000")
add_custom_command(
    OUTPUT "${AOT_GAME_WASM}"
    COMMAND ${PORT_WASM_LD} --fatal-warnings --no-entry --export-all --import-undefined
            --no-stack-first --global-base=${SHIM_MEMORY} -z stack-size=65536
            --initial-memory=${AOT_GAME_MEMORY} --max-memory=${AOT_GAME_MEMORY}
            ${AOT_GAME_OBJECTS} -o "${AOT_GAME_WASM}"
    DEPENDS ${AOT_GAME_OBJECTS}
    COMMENT "Linking the 64-bit base-game module"
    VERBATIM)
add_custom_command(
    OUTPUT "${AOT_GAME_C}" "${AOT_GAME_H}"
    COMMAND ${PORT_WASM2C} "${AOT_GAME_WASM}" -n rock_neo -o "${AOT_GAME_C}"
    COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/aot/alias_wasm_memory.py" "${AOT_GAME_C}"
    DEPENDS "${AOT_GAME_WASM}" aot/alias_wasm_memory.py
    VERBATIM)
function(game64_dispatch_source header output)
    add_custom_command(
        OUTPUT "${output}"
        COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/tools
                $<TARGET_FILE:Python3::Interpreter> ${CMAKE_CURRENT_SOURCE_DIR}/aot/gen_dispatch.py
                "${PORT_RETAIL_ELF}" "${header}" "${output}"
        DEPENDS "${header}" "${PORT_RETAIL_ELF}" aot/gen_dispatch.py tools/gen_link.py
        VERBATIM)
endfunction()

set(AOT_GAME_DISPATCH "${GEN}/game/native_dispatch.c")
game64_dispatch_source("${AOT_GAME_H}" "${AOT_GAME_DISPATCH}")
add_library(game64_module STATIC EXCLUDE_FROM_ALL "${AOT_GAME_C}" "${AOT_GAME_H}"
    "${AOT_GAME_DISPATCH}" aot/game_host.c)
target_compile_features(game64_module PUBLIC c_std_11)
target_include_directories(game64_module PUBLIC "${GEN}/game" "${PORT_WABT_INCLUDE}" PRIVATE aot)
target_compile_definitions(game64_module PUBLIC WASM_RT_MEMCHECK_BOUNDS_CHECK=1)

# Run a cross-module game call through native code before the full game imports
# are implemented. The only import used by the probe is the dispatch bridge.
set(AOT_GAME_CHECK_WASM "${GEN}/game/game_probe.wasm")
set(AOT_GAME_CHECK_C "${GEN}/game/game_probe.c")
set(AOT_GAME_CHECK_H "${GEN}/game/game_probe.h")
add_custom_command(
    OUTPUT "${AOT_GAME_CHECK_WASM}"
    COMMAND ${PORT_WASM_LD} --fatal-warnings --no-entry --export=func_8001E3F0
            --export=func_800665FC --export=func_80066750
            --no-stack-first --global-base=${SHIM_MEMORY} -z stack-size=65536
            --initial-memory=${AOT_GAME_MEMORY} --max-memory=${AOT_GAME_MEMORY}
            ${AOT_GAME_OBJECTS} -o "${AOT_GAME_CHECK_WASM}"
    DEPENDS ${AOT_GAME_OBJECTS}
    VERBATIM)
add_custom_command(
    OUTPUT "${AOT_GAME_CHECK_C}" "${AOT_GAME_CHECK_H}"
    COMMAND ${PORT_WASM2C} "${AOT_GAME_CHECK_WASM}" -n game_probe -o "${AOT_GAME_CHECK_C}"
    COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/aot/alias_wasm_memory.py" "${AOT_GAME_CHECK_C}"
    DEPENDS "${AOT_GAME_CHECK_WASM}" aot/alias_wasm_memory.py
    VERBATIM)
set(PORT_RETAIL_EXE ${REPO}/disc/extracted/ROCK_NEO.EXE CACHE FILEPATH
    "The owner's ROCK_NEO.EXE")
set(AOT_GAME_CHECK_DISPATCH "${GEN}/game/probe_dispatch.c")
game64_dispatch_source("${AOT_GAME_CHECK_H}" "${AOT_GAME_CHECK_DISPATCH}")
add_executable(game64_check aot/game64_check.c aot/game_host.c "${AOT_GAME_CHECK_C}"
    "${AOT_GAME_CHECK_H}" "${AOT_GAME_CHECK_DISPATCH}")
target_include_directories(game64_check PRIVATE "${GEN}/game")
target_link_libraries(game64_check PRIVATE port_boot64)
add_test(NAME game64_check COMMAND game64_check "${PORT_RETAIL_EXE}")
set_tests_properties(game64_check PROPERTIES TIMEOUT 15)

set(AOT_GAME_IMPORTS "${GEN}/game/imports.c")
set(AOT_GAME_IMPORT_ADDRESSES "${GEN}/game/import_addresses.h")
add_custom_command(
    OUTPUT "${AOT_GAME_IMPORTS}" "${AOT_GAME_IMPORT_ADDRESSES}"
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/tools
            $<TARGET_FILE:Python3::Interpreter> ${CMAKE_CURRENT_SOURCE_DIR}/aot/gen_imports.py
            "${PORT_RETAIL_ELF}" "${AOT_GAME_H}" "${AOT_GAME_IMPORTS}" "${AOT_GAME_IMPORT_ADDRESSES}"
    DEPENDS "${AOT_GAME_H}" "${PORT_RETAIL_ELF}" aot/gen_imports.py tools/gen_link.py
    VERBATIM)
add_executable(mml_game64 aot/game_main.c aot/game_imports.c
    "${AOT_GAME_IMPORTS}" "${AOT_GAME_IMPORT_ADDRESSES}")
target_link_libraries(mml_game64 PRIVATE game64_module port_boot64)
# The mods (port/mods/): the same sources as the 32-bit port, with their hooks on compiled hook
# points (aot/mods_host.c, MOD_HOOKS in aot/bind_retail.py).
target_sources(mml_game64 PRIVATE aot/mods_host.c mods/mods.c mods/mods_menu.c mods/mods_list.c
    mods/mod_fast_skates.c mods/mod_skate_shoot.c mods/mod_skate_quick_start.c
    mods/mod_teleport.c mods/mod_teleport_dests.c mods/mod_weapon_switch.c)
target_include_directories(mml_game64 PRIVATE mods runtime)
target_compile_definitions(mml_game64 PRIVATE PORT_AOT_MIPS=1)
target_compile_definitions(mml_game64 PRIVATE PORT_DEFAULT_EXE="${PORT_RETAIL_EXE}"
    PORT_DEFAULT_DISC="${PORT_DISC_IMAGE}" PORT_DEFAULT_SHIM="${PORT_SHIM_EXE}")

add_test(NAME game64_smoke COMMAND mml_game64
    --script "${CMAKE_CURRENT_SOURCE_DIR}/tests/smoke.script"
    --card1 "${CMAKE_CURRENT_BINARY_DIR}/game64-smoke.mcd")
set_tests_properties(game64_smoke PROPERTIES TIMEOUT 90
    PASS_REGULAR_EXPRESSION "stopping [(]script complete[)]")


set(PORT_64_OVERLAYS "all" CACHE STRING
    "Semicolon-separated overlay modules built into the 64-bit host, or all")
set(OVL64_SELECTED ${PORT_64_OVERLAYS})
if(PORT_64_OVERLAYS STREQUAL "all")
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${REPO}/tools/overlays.txt")
    file(STRINGS "${REPO}/tools/overlays.txt" OVL64_LIST REGEX "^r3_")
    set(OVL64_SELECTED)
    foreach(line IN LISTS OVL64_LIST)
        string(REGEX MATCH "^[a-z0-9_]+" mod "${line}")
        list(APPEND OVL64_SELECTED "${mod}")
    endforeach()
endif()
list(REMOVE_DUPLICATES OVL64_SELECTED)
set(OVL64_REGISTRY "")
set(OVL64_SLOT 0)
add_custom_target(overlay64_wasm)
foreach(OVL64_PROBE IN LISTS OVL64_SELECTED)
set(OVL64_ELF "${REPO}/build/${OVL64_PROBE}/${OVL64_PROBE}.elf")
set(OVL64_LD "${REPO}/build/${OVL64_PROBE}/${OVL64_PROBE}.ld")
    if(NOT EXISTS "${OVL64_ELF}" OR NOT EXISTS "${OVL64_LD}")
        message(STATUS "64-bit overlay ${OVL64_PROBE} uses the interpreter until its matching build is available")
        continue()
    endif()
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${OVL64_LD}")
    file(STRINGS "${OVL64_LD}" OVL64_LINES REGEX "build/${OVL64_PROBE}/src/.*\\.o\\(")
    set(OVL64_SOURCES)
    foreach(line IN LISTS OVL64_LINES)
        string(REGEX MATCH "build/${OVL64_PROBE}/(src/[^ ]*)\\.o\\(" _ "${line}")
        list(APPEND OVL64_SOURCES "${REPO}/${CMAKE_MATCH_1}.c")
    endforeach()
    list(REMOVE_DUPLICATES OVL64_SOURCES)
    game64_compile_objects(OVL64_OBJECTS "${GEN}/${OVL64_PROBE}" "${OVL64_ELF}"
        "${OVL64_PROBE}" ${OVL64_SOURCES})
    add_custom_target(overlay64_${OVL64_PROBE}_objects DEPENDS ${OVL64_OBJECTS})
    set(OVL64_DIR "${GEN}/${OVL64_PROBE}")
    set(OVL64_WASM "${OVL64_DIR}/${OVL64_PROBE}.wasm")
    set(OVL64_C "${OVL64_DIR}/overlay.c")
    set(OVL64_H "${OVL64_DIR}/overlay.h")
    if(OVL64_SLOT GREATER_EQUAL 44)
        message(FATAL_ERROR "64-bit overlay data slots exhausted")
    endif()
    math(EXPR OVL64_GLOBAL_BASE "${SHIM_MEMORY} + 0x100000 + ${OVL64_SLOT} * 0x20000")
    math(EXPR OVL64_SLOT "${OVL64_SLOT} + 1")
    add_custom_command(
        OUTPUT "${OVL64_WASM}"
        COMMAND ${PORT_WASM_LD} --fatal-warnings --no-entry --export-all --import-memory
                --import-undefined --no-stack-first --global-base=${OVL64_GLOBAL_BASE} -z stack-size=0
                --initial-memory=${AOT_GAME_MEMORY} --max-memory=${AOT_GAME_MEMORY}
                ${OVL64_OBJECTS} -o "${OVL64_WASM}"
        DEPENDS ${OVL64_OBJECTS}
        VERBATIM)
    add_custom_target(overlay64_${OVL64_PROBE}_wasm DEPENDS "${OVL64_WASM}")
    add_dependencies(overlay64_wasm overlay64_${OVL64_PROBE}_wasm)
    add_custom_command(
        OUTPUT "${OVL64_C}" "${OVL64_H}"
        COMMAND ${PORT_WASM2C} "${OVL64_WASM}" -n "${OVL64_PROBE}" -o "${OVL64_C}"
        COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/aot/namespace_overlay.py"
                "${OVL64_PROBE}" "${OVL64_C}" "${OVL64_H}"
        COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/aot/alias_wasm_memory.py" "${OVL64_C}"
        DEPENDS "${OVL64_WASM}" aot/alias_wasm_memory.py aot/namespace_overlay.py
        VERBATIM)
    set(OVL64_DISPATCH "${OVL64_DIR}/dispatch.c")
    set(OVL64_IMPORTS "${OVL64_DIR}/imports.c")
    set(OVL64_ADDRESSES "${OVL64_DIR}/import_addresses.h")
    add_custom_command(
        OUTPUT "${OVL64_DISPATCH}" "${OVL64_IMPORTS}" "${OVL64_ADDRESSES}"
        COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/tools
                $<TARGET_FILE:Python3::Interpreter> ${CMAKE_CURRENT_SOURCE_DIR}/aot/gen_dispatch.py
                --overlay "${OVL64_PROBE}" "${OVL64_ELF}" "${OVL64_H}" "${OVL64_DISPATCH}"
        COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/tools
                $<TARGET_FILE:Python3::Interpreter> ${CMAKE_CURRENT_SOURCE_DIR}/aot/gen_imports.py
                --overlay-elf "${OVL64_ELF}" "${PORT_RETAIL_ELF}" "${OVL64_H}"
                "${OVL64_IMPORTS}" "${OVL64_ADDRESSES}"
        DEPENDS "${OVL64_H}" "${OVL64_ELF}" "${PORT_RETAIL_ELF}" aot/gen_dispatch.py
                aot/gen_imports.py tools/gen_link.py tools/ovl_elf.py
        VERBATIM)
    set(OVL64_TARGET overlay64_${OVL64_PROBE})
    add_library(${OVL64_TARGET} STATIC "${OVL64_C}" "${OVL64_H}"
        "${OVL64_DISPATCH}" "${OVL64_IMPORTS}")
    target_link_libraries(mml_game64 PRIVATE ${OVL64_TARGET})
    target_include_directories(${OVL64_TARGET} PRIVATE aot "${PORT_WABT_INCLUDE}")
    target_compile_features(${OVL64_TARGET} PRIVATE c_std_11)
    target_compile_definitions(${OVL64_TARGET} PRIVATE PORT_NATIVE_OVERLAYS WASM_RT_MEMCHECK_BOUNDS_CHECK=1)
    string(APPEND OVL64_REGISTRY "AOT_OVERLAY(${OVL64_PROBE})\n")
endforeach()

if(OVL64_REGISTRY)
    file(GENERATE OUTPUT "${GEN}/overlay_registry.inc" CONTENT "${OVL64_REGISTRY}")
    target_include_directories(mml_game64 PRIVATE "${GEN}")
    target_sources(mml_game64 PRIVATE aot/native_overlays.c)
    target_compile_definitions(mml_game64 PRIVATE PORT_NATIVE_OVERLAYS)
endif()
if(TARGET overlay64_r3_st00)
    add_test(NAME game64_overlay_compare COMMAND ${CMAKE_COMMAND} -E env
        "PORT_TEST_BIN=$<TARGET_FILE:mml_game64>" "${CMAKE_CURRENT_SOURCE_DIR}/tests/compare.sh"
        --skip-boot)
    set_tests_properties(game64_overlay_compare PROPERTIES TIMEOUT 120)
endif()
