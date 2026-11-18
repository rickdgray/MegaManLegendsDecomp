# The Apple TV app. Built on the Mac by port/appletv/deploy.sh from a directory holding:
#   CMakeLists.txt, Info.plist   this folder
#   src/                         port/appletv/export.py's output (sources.cmake and the C)
#   game/                        ROCK_NEO.EXE, SLUS_006.03 and disc/ (the .cue and .bin)
# SDL3 comes from a static tvOS build (SDL3_DIR).
cmake_minimum_required(VERSION 3.24)
project(MegaManLegends C)

set(MML_TEAM "" CACHE STRING "Apple development team ID that signs the app (deploy.sh: TEAM)")
set(MML_BUNDLE_ID "com.example.megamanlegends" CACHE STRING "Bundle identifier (deploy.sh: BUNDLE)")
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GAME ${CMAKE_CURRENT_SOURCE_DIR}/game)

find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3-static)
include(${SRC}/sources.cmake)

# The game is in the group libraries; Xcode needs one source of the app's own to compile and link.
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/app.c "// The game's code is in the mml_g* libraries.\n")
# tvOS: the app. macOS (for debugging the same code on the Mac): a plain command-line program,
# run as `mml --disc game/disc --shim game/SLUS_006.03 game/ROCK_NEO.EXE [--window]`.
if(CMAKE_SYSTEM_NAME STREQUAL "tvOS")
    set(MML_APP_DEFS PORT_APPLETV)
    # The icon and top shelf images (icon/make.py): Xcode compiles the asset catalog.
    set(MML_ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/Assets.xcassets)
    set_source_files_properties(${MML_ASSETS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    add_executable(mml MACOSX_BUNDLE ${CMAKE_CURRENT_BINARY_DIR}/app.c ${MML_ASSETS})
    set_target_properties(mml PROPERTIES
        XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "App Icon & Top Shelf Image")
else()
    set(MML_APP_DEFS)
    add_executable(mml ${CMAKE_CURRENT_BINARY_DIR}/app.c)
endif()
set_target_properties(mml PROPERTIES
    OUTPUT_NAME "MegaManLegends"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${MML_BUNDLE_ID}
    XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ${MML_TEAM}
    XCODE_ATTRIBUTE_CODE_SIGN_STYLE Automatic
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY 3
    XCODE_ATTRIBUTE_GCC_OPTIMIZATION_LEVEL 2)

math(EXPR last "${MML_GROUPS} - 1")
foreach(n RANGE ${last})
    list(TRANSFORM MML_GROUP_${n}_SOURCES PREPEND ${SRC}/)
    list(TRANSFORM MML_GROUP_${n}_INCLUDES PREPEND ${SRC}/)
    add_library(mml_g${n} STATIC ${MML_GROUP_${n}_SOURCES})
    target_compile_definitions(mml_g${n} PRIVATE ${MML_GROUP_${n}_DEFINES}
        ${MML_APP_DEFS} PORT_SINGLE_PROCESS PORT_DEFAULT_EXE="" PORT_DEFAULT_DISC=""
        PORT_DEFAULT_SHIM="")
    target_include_directories(mml_g${n} PRIVATE ${MML_GROUP_${n}_INCLUDES})
    target_link_libraries(mml_g${n} PRIVATE SDL3::SDL3-static)
    set_target_properties(mml_g${n} PROPERTIES C_STANDARD 11
        XCODE_ATTRIBUTE_GCC_OPTIMIZATION_LEVEL 2)
    target_compile_options(mml_g${n} PRIVATE -w -fno-strict-aliasing)
    # main (SDL_main) is in one of these: force it in, the rest follows by reference.
    target_link_libraries(mml PRIVATE "-Wl,-force_load,$<TARGET_FILE:mml_g${n}>")
    add_dependencies(mml mml_g${n})
endforeach()
target_link_libraries(mml PRIVATE SDL3::SDL3-static)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "tvOS")
    return()
endif()
# The disc goes into the bundle as game/ (about 500 MB), copied only when it changed.
# Xcode gives the script phase the bundle's location (TARGET_BUILD_DIR, WRAPPER_NAME).
add_custom_command(TARGET mml POST_BUILD
    COMMAND sh -c "rsync -a '${GAME}/' \"$TARGET_BUILD_DIR/$WRAPPER_NAME/game/\""
    VERBATIM)
