cmake_minimum_required(VERSION 3.27)
project(big-homework-1)

set(CMAKE_CXX_STANDARD 17)

add_executable(big-homework-1
        main.cpp
        database/decorator/Decorator.h
        src/exporter/SaveData.h
        src/executor/Invoker.h
        src/executor/ProcessRequest.h
        src/observer/Observer.h
        src/helper.h
        src/factory/CommandFactory.h
        tests/tests.cpp
        database/decorator/Logger.h
        database/decorator/Facade.h
        database/decorator/RetryDecorator.h
)

# ---------------------------------------------------------------
include_directories("/opt/homebrew/Cellar/curl/8.12.0/include")
link_directories("/opt/homebrew/Cellar/curl/8.12.0/lib")

include_directories("/opt/homebrew/opt/libpqxx/include")
link_directories("/opt/homebrew/opt/libpqxx/lib")

include_directories("third_party/libpqxx/include")
include_directories("/opt/homebrew/opt/openssl@3/include")
# ---------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

find_package(GTest REQUIRED)
enable_testing()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
add_executable(tests tests/tests.cpp)

target_link_libraries(big-homework-1
        PRIVATE
        spdlog::spdlog
        /opt/homebrew/opt/openssl@3/lib/libssl.dylib
        /opt/homebrew/opt/openssl@3/lib/libcrypto.dylib
        /opt/homebrew/opt/libpqxx/lib/libpqxx.dylib
)