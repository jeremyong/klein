include(FetchContent)

find_package(benchmark)

if(NOT benchmark_FOUND)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.5.0
    )
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark testing")
    set(BENCHMARK_ENABLE_LTO ON CACHE BOOL "Enable benchmark link time optimization")
    set(BENCHMARK_BUILD_32_BITS OFF CACHE BOOL "Never enable 32-bit builds of the benchmark library")
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark install")
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable benchmark gtests")
    FetchContent_MakeAvailable(benchmark)
    add_library(benchmark::benchmark ALIAS benchmark)
endif()

find_package(glm)

if(NOT glm_FOUND)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.7
    )
    FetchContent_MakeAvailable(glm)
endif()

add_executable(klein_bench bench.cpp)
target_link_libraries(klein_bench PRIVATE benchmark::benchmark klein)
set_target_properties(klein_bench
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

# For MSVC, be sure to compile the benchmark in release mode to get accurate timings
if(NOT MSVC)
    target_compile_options(
        klein_bench
        PRIVATE
        -O2 -msse4.2 -fno-exceptions -fno-rtti -save-temps -masm=intel
    )
    target_link_options(klein_bench PRIVATE -flto)
endif()

add_executable(glm_bench glm_bench.cpp)
target_link_libraries(glm_bench PRIVATE benchmark::benchmark glm)
set_target_properties(glm_bench
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)
if(NOT MSVC)
    target_compile_options(
        glm_bench PRIVATE -O2 -pipe -msse4.2
        PRIVATE
        -O2 -pipe -msse4.2 -fno-exceptions -fno-rtti
    )
    target_link_options(glm_bench PRIVATE -flto)
endif()