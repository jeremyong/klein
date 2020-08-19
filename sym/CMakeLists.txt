add_library(symlib ga.cpp repl.cpp parser.cpp poly.cpp)
target_compile_features(symlib PUBLIC cxx_std_17)

if(NOT MSVC)
# Needed for popcnt intrinsic
    target_compile_options(symlib PUBLIC -msse4.2)
endif()

add_executable(klein_shell main.cpp)
target_link_libraries(klein_shell PRIVATE symlib)
set_target_properties(klein_shell
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

if(KLEIN_ENABLE_TESTS)
    add_executable(sym_test test.cpp)
    target_link_libraries(sym_test PRIVATE symlib doctest)
    target_compile_definitions(sym_test PRIVATE
        DOCTEST_CONFIG_SUPER_FAST_ASSERTS # uses a function call for asserts to speed up compilation
        DOCTEST_CONFIG_USE_STD_HEADERS # prevent non-standard overloading of std declarations
        DOCTEST_CONFIG_INCLUDE_TYPE_TRAITS # enable doctest::Approx() to take any argument explicitly convertible to a double
        DOCTEST_CONFIG_NO_POSIX_SIGNALS
        DOCTEST_CONFIG_NO_EXCEPTIONS
    )
    set_target_properties(sym_test
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
    )
endif()