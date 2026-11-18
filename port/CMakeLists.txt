# Native port of Mega Man Legends.
#
#   cmake -S port -B build/port -G Ninja && ninja -C build/port
#
# Targets:
#   rock_neo_game  every src/rock_neo.exe/*.c, plus port/game/*.c (C for the hand-written
#                  assembly), compiled natively as 32-bit x86 (object library)
#   port_native    the native PsyQ libraries (port/psyq/) and the asm_fastmem equivalents
#   game_check     tries the files excluded below too, to see whether they compile yet
#   memtest        addressing proof (32-bit, no SDL)
#   harness        calls decompiled game functions natively with the retail data image loaded
#   mml            the game: ROCK_NEO.EXE's main, natively (headless until lib32-sdl3)
#   rt_test        SDL3 window: software GPU drawing an ordering table, live pad state
#
# Placement: the game and port_native objects are
# rewritten by tools/gen_link.py so every function and data object with a retail address has
# that address as its symbol value; the generated linker script and stub table do the rest.
#
# The game code and everything linked with it is 32-bit (-m32): the game keeps pointers in
# 32-bit fields and its data holds 32-bit addresses. rt_test links SDL3, and only the 64-bit
# SDL3 is installed now; with lib32-sdl3 installed, -DPORT_SDL_M32=ON builds it 32-bit as well,
# which is what the game executable will need.
cmake_minimum_required(VERSION 3.20)
project(mml_port C)

set(REPO ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(GEN ${CMAKE_CURRENT_BINARY_DIR}/gen)
file(MAKE_DIRECTORY ${GEN})
find_package(Python3 REQUIRED COMPONENTS Interpreter)

option(PORT_SDL_M32 "Build the SDL programs as 32-bit (needs lib32-sdl3)" OFF)
option(PORT_GAME_WARNINGS "Show compiler warnings for the game sources" OFF)
set(PORT_RETAIL_ELF ${REPO}/build/rock_neo.exe/rock_neo.exe.elf CACHE FILEPATH
    "Matching build's ELF: retail addresses and types of every symbol (make rock_neo.exe)")
set(PORT_RETAIL_EXE ${REPO}/disc/extracted/ROCK_NEO.EXE CACHE FILEPATH
    "The owner's ROCK_NEO.EXE, read at run time (make extract)")
set(PORT_DISC_IMAGE ${REPO}/disc/image CACHE PATH
    "The owner's disc image, read at run time: a .cue file or a directory holding one")
# Game files that do not compile natively yet; each needs a small change on the matching side.
set(PORT_GAME_EXCLUDE ""
    CACHE STRING "src/rock_neo.exe files left out of rock_neo_game")

set(M32 -m32)
# Flags for the game sources: GCC 2.7-era C, MIPS-like semantics (wrapping arithmetic, no
# strict aliasing; the code type-puns freely), absolute addressing (no PIC), and no builtins
# (the game has its own catan, ccos, ...). One section per function and object, and no common
# symbols, so tools/gen_link.py can place each at its retail address. No loop bounds inferred from
# array sizes (the game indexes past a row on purpose, e.g. func_8003B278), and no assumption
# that a file static is untouched by calls (retail data and literal addresses reach them too).
set(PLACE_CFLAGS -ffunction-sections -fdata-sections -fno-common)
set(GAME_CFLAGS ${M32} -std=gnu89 -fpermissive -fno-pic -fno-strict-aliasing -fwrapv
    -fno-builtin -fno-delete-null-pointer-checks -fno-stack-protector -O2 -g ${PLACE_CFLAGS}
    -fno-aggressive-loop-optimizations -fno-ipa-reference)
if(NOT PORT_GAME_WARNINGS)
    list(APPEND GAME_CFLAGS -w)
endif()
# The game's own main() becomes psx_main(); the host program owns main(). NON_MATCHING selects
# the alternative C drafts kept under #ifdef NON_MATCHING (functionally the same code).
set(GAME_CPPFLAGS -DPORT -DNON_MATCHING -Dmain=psx_main -Ulinux -Uunix -Ui386
    -include ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
    -I${CMAKE_CURRENT_SOURCE_DIR}/include -I${REPO}/include/rock_neo.exe -I${REPO}/include)

# port_game_source(<src.c> <out-var>): preprocess with the game headers, rewrite inline MIPS
# into interpreter calls, and return the generated file to compile.
function(port_game_source src out_var)
    get_filename_component(name ${src} NAME_WE)
    set(i ${GEN}/${name}.i)
    set(out ${GEN}/${name}.port.c)
    add_custom_command(
        OUTPUT ${out}
        COMMAND ${CMAKE_C_COMPILER} ${GAME_CPPFLAGS} ${M32} -std=gnu89 -E ${src} -o ${i}
        COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/tools/asm_rewrite.py ${i} ${out}
        DEPENDS ${src} ${CMAKE_CURRENT_SOURCE_DIR}/tools/asm_rewrite.py
                ${CMAKE_CURRENT_SOURCE_DIR}/include/port_prelude.h
        IMPLICIT_DEPENDS C ${src}
        COMMENT "Preparing ${name}.c for the native build"
        VERBATIM)
    # Already preprocessed: compile as is.
    set_source_files_properties(${out} PROPERTIES COMPILE_OPTIONS "-fpreprocessed")
    set(${out_var} ${out} PARENT_SCOPE)
endfunction()

# --- runtime ---------------------------------------------------------------------------------

set(RT_CORE runtime/psx_mem.c runtime/gpu.c runtime/pad.c runtime/memcard.c runtime/port_config.c
    runtime/port_remote.c runtime/port_overlay.c)
# The mod system (port/mods/): the vanilla/mods choice, hooks on game
# functions, the menus, and the mods. Port only; it reaches the game through retail addresses.
set(MODS_SOURCES mods/mods.c mods/mods_menu.c mods/mods_list.c mods/mod_fast_skates.c
    mods/mod_skate_shoot.c mods/mod_skate_quick_start.c mods/mod_teleport.c
    mods/mod_teleport_dests.c mods/mod_weapon_switch.c)
set(RT_GAME runtime/gte.c runtime/mips_asm.c runtime/mips_cpu.c runtime/port_missing.c
    runtime/port_stubs.c runtime/port_game.c runtime/port_script.c runtime/overlay.c runtime/psx_io.c runtime/spu.c runtime/mdec.c
    runtime/port_audio.c)
set(RT_WARN -Wall -Wextra -Wno-unused-parameter -O2 -g)

add_library(port_rt32 STATIC ${RT_CORE} ${RT_GAME} ${MODS_SOURCES})
target_include_directories(port_rt32 PUBLIC runtime mods)
target_compile_options(port_rt32 PRIVATE ${M32} -fno-pic ${RT_WARN})
target_link_options(port_rt32 INTERFACE ${M32} -no-pie)
target_link_libraries(port_rt32 INTERFACE m)

# Native code that stands at retail addresses: the PsyQ libraries on the runtime, and the C
# equivalents of asm_fastmem. Placed like the game code.
set(NATIVE_SOURCES psyq/libgpu.c psyq/libgte.c psyq/libetc.c psyq/libapi.c psyq/libcd.c
    runtime/asm_native.c)
add_library(port_native OBJECT ${NATIVE_SOURCES})
target_include_directories(port_native PRIVATE runtime)
target_compile_options(port_native PRIVATE ${M32} -fno-pic -fno-builtin ${RT_WARN} ${PLACE_CFLAGS})

# PsyQ routines run from the retail image by the MIPS interpreter: linked, never placed. libsnd
# and libspu are among them (their hardware accesses reach the software SPU).
add_library(port_emulated OBJECT psyq/psyq_emulated.c psyq/libsnd.c)
target_include_directories(port_emulated PRIVATE runtime)
target_compile_options(port_emulated PRIVATE ${M32} -fno-pic -fno-builtin ${RT_WARN})

# --- game code -------------------------------------------------------------------------------

file(GLOB GAME_SOURCES CONFIGURE_DEPENDS ${REPO}/src/rock_neo.exe/*.c
     ${CMAKE_CURRENT_SOURCE_DIR}/game/*.c)
set(GAME_GEN)
set(GAME_GEN_ALL)
set(PLACED)
foreach(src ${GAME_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    port_game_source(${src} out)
    list(APPEND GAME_GEN_ALL ${out})
    if(NOT name IN_LIST PORT_GAME_EXCLUDE)
        list(APPEND GAME_GEN ${out})
        list(APPEND PLACED ${GEN}/placed/${name}.port.c.o)
    endif()
endforeach()
foreach(src ${NATIVE_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    list(APPEND PLACED ${GEN}/placed/${name}.c.o)
endforeach()

add_library(rock_neo_game OBJECT ${GAME_GEN})
target_compile_options(rock_neo_game PRIVATE ${GAME_CFLAGS})

# game_check: compile every file, excluded ones included; `ninja -k 0 game_check` lists failures.
add_library(game_check OBJECT EXCLUDE_FROM_ALL ${GAME_GEN_ALL})
target_compile_options(game_check PRIVATE ${GAME_CFLAGS})

# --- tests -----------------------------------------------------------------------------------

add_executable(memtest tests/memtest.c)
target_compile_options(memtest PRIVATE ${M32} -fno-pic ${RT_WARN})
target_link_libraries(memtest PRIVATE port_rt32)

if(EXISTS ${PORT_RETAIL_ELF})
    port_game_source(${CMAKE_CURRENT_SOURCE_DIR}/tests/gte_case.c GTE_CASE)
    add_library(harness_game OBJECT ${GTE_CASE})
    target_compile_options(harness_game PRIVATE ${GAME_CFLAGS})

    add_library(harness_main OBJECT tests/harness.c)
    target_compile_options(harness_main PRIVATE ${M32} -fno-pic -fno-builtin ${RT_WARN})
    target_compile_definitions(harness_main PRIVATE PORT_DEFAULT_EXE="${PORT_RETAIL_EXE}")
    target_include_directories(harness_main PRIVATE runtime)

    add_library(mml_main OBJECT runtime/host_main.c)
    target_compile_options(mml_main PRIVATE ${M32} -fno-pic ${RT_WARN})
    target_compile_definitions(mml_main PRIVATE PORT_DEFAULT_EXE="${PORT_RETAIL_EXE}"
                               PORT_DEFAULT_DISC="${PORT_DISC_IMAGE}")
    target_include_directories(mml_main PRIVATE runtime mods)

    # Placement, stubs and absolute symbols for retail data.
    add_custom_command(
        OUTPUT ${PLACED} ${GEN}/stubs.c ${GEN}/retail.ld ${GEN}/link_report.txt
        COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_link.py
                --elf ${PORT_RETAIL_ELF} --out-dir ${GEN}/placed
                --stubs ${GEN}/stubs.c --ld ${GEN}/retail.ld --report ${GEN}/link_report.txt
                --place $<TARGET_OBJECTS:rock_neo_game> $<TARGET_OBJECTS:port_native>
                --scan $<TARGET_OBJECTS:port_emulated> $<TARGET_OBJECTS:harness_game>
                       $<TARGET_OBJECTS:harness_main> $<TARGET_OBJECTS:mml_main>
                --defined $<TARGET_FILE:port_rt32>
        DEPENDS rock_neo_game port_native port_emulated harness_game harness_main mml_main
                port_rt32 ${PORT_RETAIL_ELF} ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_link.py
                $<TARGET_OBJECTS:rock_neo_game> $<TARGET_OBJECTS:port_native>
        COMMENT "Placing the game at retail addresses"
        COMMAND_EXPAND_LISTS
        VERBATIM)
    set_source_files_properties(${PLACED} PROPERTIES EXTERNAL_OBJECT TRUE GENERATED TRUE)

    # port_link_game(<target> <main objects>): the placed game, the stub table and the runtime.
    function(port_link_game target)
        add_executable(${target} ${GEN}/stubs.c ${PLACED} ${ARGN}
                       $<TARGET_OBJECTS:port_emulated>)
        target_compile_options(${target} PRIVATE ${M32} -fno-pic -w)
        target_include_directories(${target} PRIVATE runtime)
        target_link_libraries(${target} PRIVATE port_rt32)
        # The script assigns symbols and places file statics; INSERT keeps the default script.
        target_link_options(${target} PRIVATE -Wl,-T,${GEN}/retail.ld)
        set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS ${GEN}/retail.ld)
    endfunction()

    port_link_game(harness $<TARGET_OBJECTS:harness_main> $<TARGET_OBJECTS:harness_game>)
    port_link_game(mml $<TARGET_OBJECTS:mml_main>)
    include(overlays.cmake) # the overlay C, natively, into mml and harness
    include(shim.cmake) # the boot shim: mml_boot, which runs mml with LoadExec
else()
    message(WARNING "No ${PORT_RETAIL_ELF}: build rock_neo.exe first; harness and mml skipped")
endif()

# --- SDL programs ----------------------------------------------------------------------------

find_package(PkgConfig REQUIRED)
if(PORT_SDL_M32)
    set(ENV{PKG_CONFIG_LIBDIR} /usr/lib32/pkgconfig)
    set(HOST_ARCH ${M32})
else()
    set(HOST_ARCH)
endif()
pkg_check_modules(SDL3 IMPORTED_TARGET sdl3)

add_library(port_rt_host STATIC ${RT_CORE})
target_include_directories(port_rt_host PUBLIC runtime)
target_compile_options(port_rt_host PRIVATE ${HOST_ARCH} ${RT_WARN})

add_executable(rt_test tests/rt_test.c)
target_compile_options(rt_test PRIVATE ${HOST_ARCH} ${RT_WARN})
target_link_options(rt_test PRIVATE ${HOST_ARCH})
target_link_libraries(rt_test PRIVATE port_rt_host m)
if(SDL3_FOUND)
    target_sources(rt_test PRIVATE runtime/platform_sdl.c)
    target_compile_definitions(rt_test PRIVATE PORT_HAVE_SDL)
    target_link_libraries(rt_test PRIVATE PkgConfig::SDL3)
else()
    message(WARNING "SDL3 not found for this architecture: rt_test runs headless only")
endif()

# The game's window: with 32-bit SDL3 (PORT_SDL_M32=ON and lib32-sdl3), mml opens one; without,
# it runs headless only (--headless).
if(PORT_SDL_M32 AND SDL3_FOUND AND TARGET mml)
    target_sources(port_rt32 PRIVATE runtime/platform_sdl.c)
    target_compile_definitions(port_rt32 PRIVATE PORT_HAVE_SDL)
    target_link_libraries(port_rt32 PUBLIC PkgConfig::SDL3)
endif()
