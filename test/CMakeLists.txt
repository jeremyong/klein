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
    test_gp.cpp
    test_rp.cpp
    test_sw.cpp
)
target_link_libraries(klein_test PRIVATE klein doctest)
target_compile_definitions(klein_test PRIVATE
    DOCTEST_CONFIG_SUPER_FAST_ASSERTS # uses a function call for asserts to speed up compilation
    DOCTEST_CONFIG_USE_STD_HEADERS # prevent non-standard overloading of std declarations
    DOCTEST_CONFIG_INCLUDE_TYPE_TRAITS # enable doctest::Approx() to take any argument explicitly convertible to a double
    DOCTEST_CONFIG_NO_POSIX_SIGNALS
    DOCTEST_CONFIG_NO_EXCEPTIONS
)
if (NOT MSVC)
    target_compile_options(klein_test PRIVATE -fno-omit-frame-pointer -fsanitize=address)
    target_link_options(klein_test PRIVATE -fno-omit-frame-pointer -fsanitize=address)
endif()
# Place the test executable at the project binary directory instead of in the nested subfolder
set_target_properties(klein_test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)