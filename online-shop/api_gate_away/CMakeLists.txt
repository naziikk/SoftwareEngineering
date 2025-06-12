cmake_minimum_required(VERSION 3.22)
project(ApiGateAway)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        config/config.h
        config/config.cpp
        utils.h
)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml-cpp)

include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)
find_package(spdlog REQUIRED)

add_executable(ApiGateAway ${SOURCE_FILES})

target_link_libraries(ApiGateAway PRIVATE
        yaml-cpp
        spdlog::spdlog
)

