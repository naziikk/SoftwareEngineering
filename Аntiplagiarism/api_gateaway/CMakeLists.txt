cmake_minimum_required(VERSION 3.27)
project(ApiGateaway)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        controllers/analyzing_controller.h
        controllers/creating_controller.h
        controllers/receiver_controller.h
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

add_executable(ApiGateaway ${SOURCE_FILES})

target_link_libraries(ApiGateaway PRIVATE
        yaml-cpp
)

