cmake_minimum_required(VERSION 3.22)
project(OrdersService)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        infrastructure/database/Database.h
        infrastructure/database/Database.cpp
        infrastructure/config/config.h
        infrastructure/config/config.cpp
        controllers/get_orders_controller.cpp
        controllers/get_orders_controller.h
        app/orders.h
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


add_executable(OrdersService ${SOURCE_FILES})

target_include_directories(OrdersService PRIVATE ${pqxx_SOURCE_DIR}/include)

target_link_libraries(OrdersService PRIVATE
        yaml-cpp
        pqxx
        CURL::libcurl
        OpenSSL::SSL
        OpenSSL::Crypto
)

