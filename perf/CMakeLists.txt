include(FetchContent)

if(NOT WIN32)
    find_package(glm)
endif()

if(NOT glm_FOUND)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.7
    )
    FetchContent_MakeAvailable(glm)
endif()

FetchContent_Declare(
    rtm
    GIT_REPOSITORY git@github.com:nfrechette/rtm.git
    GIT_TAG origin/master
)
if(NOT rtm_POPULATED)
    FetchContent_Populate(rtm)
    # RTM doesn't provide an option to avoid building tests and doesn't actually have
    # a nice cmake interface target to link against, so don't add it as a subdirectory
endif()

FetchContent_Declare(
    mc_ruler
    GIT_REPOSITORY https://github.com/jeremyong/mc_ruler.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(mc_ruler)

include(MCRuler)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_library(klein_perf klein_perf.cpp)
    target_link_libraries(klein_perf PRIVATE mc_ruler::mc_ruler klein)
    mc_ruler(klein_perf SOURCES klein_perf.cpp)

    add_library(glm_perf glm_perf.cpp)
    target_link_libraries(glm_perf PRIVATE mc_ruler::mc_ruler glm)
    mc_ruler(glm_perf SOURCES glm_perf.cpp)

    add_library(rtm_perf rtm_perf.cpp)
    target_link_libraries(rtm_perf PRIVATE mc_ruler::mc_ruler)
    target_include_directories(rtm_perf PRIVATE ${rtm_SOURCE_DIR}/includes)
    mc_ruler(rtm_perf SOURCES rtm_perf.cpp)
endif()