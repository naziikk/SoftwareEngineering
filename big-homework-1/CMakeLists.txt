cmake_minimum_required(VERSION 3.27)
project(big-homework-1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        database/decorator/Decorator.h
        src/exporter/SaveData.h
        src/executor/Invoker.h
        src/executor/ProcessRequest.h
        src/observer/Observer.h
        src/helper.h
        src/factory/CommandFactory.h
        database/decorator/Logger.h
        database/decorator/Facade.h
        database/decorator/RetryDecorator.h
)

include(FetchContent)

# Подключаем spdlog
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
        pqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG 7.9.1
)
FetchContent_MakeAvailable(pqxx)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)

add_executable(big-homework-1 ${SOURCE_FILES})

target_include_directories(big-homework-1 PRIVATE ${pqxx_SOURCE_DIR}/include)

target_link_libraries(big-homework-1
        PRIVATE
        spdlog::spdlog
        pqxx
        CURL::libcurl
        OpenSSL::SSL
        OpenSSL::Crypto
)