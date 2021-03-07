include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    GIT_TAG 2.3.6
)
FetchContent_MakeAvailable(doctest)

list(APPEND CMAKE_MODULE_PATH ${doctest_SOURCE_DIR}/scripts/cmake)

add_executable(klein_test
    main.cpp
    test_ep.cpp
    test_exp_log.cpp
    test_ip.cpp
    test_gp.cpp
    test_metric.cpp
    test_rp.cpp
    test_sse.cpp
    test_sw.cpp
)
target_link_libraries(klein_test PRIVATE klein::klein doctest)
target_compile_features(klein_test PRIVATE cxx_std_17)
target_compile_definitions(klein_test PRIVATE
    DOCTEST_CONFIG_SUPER_FAST_ASSERTS # uses a function call for asserts to speed up compilation
    DOCTEST_CONFIG_USE_STD_HEADERS # prevent non-standard overloading of std declarations
    DOCTEST_CONFIG_INCLUDE_TYPE_TRAITS # enable doctest::Approx() to take any argument explicitly convertible to a double
    DOCTEST_CONFIG_NO_POSIX_SIGNALS
    DOCTEST_CONFIG_NO_EXCEPTIONS
)
if (NOT MSVC)
    target_compile_options(klein_test
        PRIVATE
        -fno-omit-frame-pointer
        -Wall
        -Wno-comment # Needed for doxygen
    )
endif()
# Place the test executable at the project binary directory instead of in the nested subfolder
set_target_properties(klein_test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_executable(klein_test_sse42
    main.cpp
    test_ep.cpp
    test_exp_log.cpp
    test_ip.cpp
    test_gp.cpp
    test_metric.cpp
    test_rp.cpp
    test_sse.cpp
    test_sw.cpp
)
target_link_libraries(klein_test_sse42 PRIVATE klein::klein_sse42 doctest)
target_compile_features(klein_test_sse42 PRIVATE cxx_std_17)
target_compile_definitions(klein_test_sse42 PRIVATE
    DOCTEST_CONFIG_SUPER_FAST_ASSERTS # uses a function call for asserts to speed up compilation
    DOCTEST_CONFIG_USE_STD_HEADERS # prevent non-standard overloading of std declarations
    DOCTEST_CONFIG_INCLUDE_TYPE_TRAITS # enable doctest::Approx() to take any argument explicitly convertible to a double
    DOCTEST_CONFIG_NO_POSIX_SIGNALS
    DOCTEST_CONFIG_NO_EXCEPTIONS
)
if (NOT MSVC)
    target_compile_options(klein_test_sse42
        PRIVATE
        -fno-omit-frame-pointer
        -fsanitize=address
        -Wall
        -Wno-comment # Needed for doxygen
    )
    target_link_options(klein_test_sse42 PRIVATE -fno-omit-frame-pointer -fsanitize=address)
endif()
# Place the test executable at the project binary directory instead of in the nested subfolder
set_target_properties(klein_test_sse42
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_executable(klein_test_cxx11
    main.cpp
    test_ep.cpp
    test_exp_log.cpp
    test_ip.cpp
    test_gp.cpp
    test_metric.cpp
    test_rp.cpp
    test_sse.cpp
    test_sw.cpp
)
target_link_libraries(klein_test_cxx11 PRIVATE klein::klein_cxx11 doctest)
target_compile_features(klein_test_cxx11 PRIVATE cxx_std_11)
target_compile_definitions(klein_test_cxx11 PRIVATE
    DOCTEST_CONFIG_SUPER_FAST_ASSERTS # uses a function call for asserts to speed up compilation
    DOCTEST_CONFIG_USE_STD_HEADERS # prevent non-standard overloading of std declarations
    DOCTEST_CONFIG_INCLUDE_TYPE_TRAITS # enable doctest::Approx() to take any argument explicitly convertible to a double
    DOCTEST_CONFIG_NO_POSIX_SIGNALS
    DOCTEST_CONFIG_NO_EXCEPTIONS
)
if (NOT MSVC)
    target_compile_options(klein_test_cxx11
        PRIVATE
        -fno-omit-frame-pointer
        -fsanitize=address
        -Wall
        -Wno-comment # Needed for doxygen
    )
    target_link_options(klein_test_cxx11 PRIVATE -fno-omit-frame-pointer -fsanitize=address)
endif()
# Place the test executable at the project binary directory instead of in the nested subfolder
set_target_properties(klein_test_cxx11
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_executable(klein_test_glsl test_glsl.cpp)
target_include_directories(klein_test_glsl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../glsl)
target_link_libraries(klein_test_glsl PRIVATE doctest)
target_compile_features(klein_test_glsl PRIVATE cxx_std_17)
target_compile_definitions(klein_test_glsl PRIVATE
    DOCTEST_CONFIG_SUPER_FAST_ASSERTS # uses a function call for asserts to speed up compilation
    DOCTEST_CONFIG_USE_STD_HEADERS # prevent non-standard overloading of std declarations
    DOCTEST_CONFIG_INCLUDE_TYPE_TRAITS # enable doctest::Approx() to take any argument explicitly convertible to a double
    DOCTEST_CONFIG_NO_POSIX_SIGNALS
    DOCTEST_CONFIG_NO_EXCEPTIONS
)
set_target_properties(klein_test_glsl
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)