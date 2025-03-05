cmake_minimum_required(VERSION 3.27)
project(big-homework-1)

set(CMAKE_CXX_STANDARD 17)

add_executable(big-homework-1 main.cpp
        database/migrations/Database.h
        src/exporter/SaveData.h
        src/executor/Invoker.h
        src/executor/ProcessRequest.h)

include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

target_link_libraries(big-homework-1
        PRIVATE
        spdlog::spdlog
)