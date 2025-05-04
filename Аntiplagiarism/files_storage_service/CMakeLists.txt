cmake_minimum_required(VERSION 3.27)
project(FilesStorageService)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        presentation/file_crud_controller.h
        presentation/file_crud_controller.cpp
        presentation/utils.h
        infrastructure/database/Database.h
        infrastructure/database/Database.cpp
        app/file_saver.cpp
        app/file_saver.h
)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml-cpp)

FetchContent_Declare(
        pqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG 7.9.1
)
FetchContent_MakeAvailable(pqxx)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)


add_executable(FilesStorageService ${SOURCE_FILES})

target_include_directories(FilesStorageService PRIVATE ${pqxx_SOURCE_DIR}/include)

target_link_libraries(FilesStorageService PRIVATE
        yaml-cpp
        pqxx
        CURL::libcurl
        OpenSSL::SSL
        OpenSSL::Crypto
)

