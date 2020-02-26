include(FetchContent)

find_package(glm)

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