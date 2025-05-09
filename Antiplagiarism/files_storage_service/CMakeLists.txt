cmake_minimum_required(VERSION 3.22)
project(FilesStorageService)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        controllers/file_crud_controller.h
        controllers/file_crud_controller.cpp
        controllers/utils.h
        infrastructure/database/Database.h
        infrastructure/database/Database.cpp
        infrastructure/config/config.cpp
        infrastructure/config/config.h
        app/file_saver.cpp
        app/file_saver.h
        app/file_content_provider.cpp
        app/file_content_provider.h
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

