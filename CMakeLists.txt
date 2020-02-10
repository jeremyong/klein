# USAGE
# Include this project transitively in your cmake project using add_subdirectory
# Alternatively, copy the contents of the public folder somewhere in your include
# path and be sure to compile with the correct architecture flags for your compiler
# Search for "target_compile_options" in this file to see what flags are needed.

cmake_minimum_required(VERSION 3.15)

project(PRStar LANGUAGES C CXX)

# Detect if we are a standalone projection or if we're included transitively
# and set the various option defaults accordingly. By default, tests and utilities
# are not built unless PRStar is built as a standalone project
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(PRSTAR_STANDALONE ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    option(PRSTAR_ENABLE_TESTS "Enable compilation of PRStar tests" ON)
    option(PRSTAR_VALIDATE "Enable runtime validations" ON)
    option(PRSTAR_BUILD_SYM "Enable compilation of symbolic PRStar utility" ON)
else()
    set(PRSTAR_STANDALONE OFF)
    option(PRSTAR_ENABLE_TESTS "Enable compilation of PRStar tests" OFF)
    option(PRSTAR_VALIDATE "Enable runtime validations" OFF)
    option(PRSTAR_BUILD_SYM "Enable compilation of symbolic PRStar utility" ON)
endif()

add_library(prstar INTERFACE)
target_include_directories(prstar INTERFACE public)
target_compile_features(prstar INTERFACE cxx_std_17)
# SSE4.2 has > 96% market penetration according to the Steam hardware survey
# queried as of December 2019 while AVX2 is around 70%. Thus, we can assume
# FMA support is at least 70%, but perhaps not much more beyond that.
# TODO: Optionally support FMA
if(MSVC)
    # On MSVC, SSE2 enables code generation of SSE2 and later (does not include
    # AVX extensions). This is on by default.
else()
    # Unlike MSVC, FMA instructions are enabled with a separate feature flag
    target_compile_options(prstar INTERFACE -msse4.2 -mfma)
endif()

if(PRSTAR_ENABLE_TESTS)
    enable_testing()

    add_subdirectory(test)
endif()

if(PRSTAR_BUILD_SYM)
    add_subdirectory(sym)
endif()
