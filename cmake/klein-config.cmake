include("${CMAKE_CURRENT_LIST_DIR}/klein-targets.cmake")

find_path(
    simde_headers
    "x86/sse4.2.h"
    PATH_SUFFIXES "simde"
)

target_include_directories(klein::klein INTERFACE ${simde_headers})
target_include_directories(klein::klein_cxx11 INTERFACE ${simde_headers})
target_include_directories(klein::klein_sse42 INTERFACE ${simde_headers})
