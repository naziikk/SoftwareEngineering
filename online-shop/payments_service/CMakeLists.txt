cmake_minimum_required(VERSION 3.22)
project(PaymentsService)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml-cpp)

FetchContent_Declare(
        cppkafka
        GIT_REPOSITORY https://github.com/mfontanini/cppkafka.git
        GIT_TAG 0.4.0
)
FetchContent_MakeAvailable(cppkafka)

FetchContent_Declare(
        pqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
)
FetchContent_MakeAvailable(pqxx)

if(APPLE)
    set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3")
    set(OPENSSL_INCLUDE_DIR "/opt/homebrew/opt/openssl@3/include")
    set(OPENSSL_LIBRARY_DIR "/opt/homebrew/opt/openssl@3/lib")
    link_directories(${OPENSSL_LIBRARY_DIR})
endif()

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)

set(SOURCE_FILES
        main.cpp
        utils.h
        controllers/account_crud_controller.cpp
        controllers/account_crud_controller.h
        infrastructure/kafka/kafka_consumer.cpp
        infrastructure/kafka/kafka_consumer.h
        infrastructure/kafka/kafka_producer.cpp
        infrastructure/kafka/kafka_producer.h
        infrastructure/database/database.h
        infrastructure/database/database.cpp
        infrastructure/config/config.h
        infrastructure/config/config.cpp
        app/account_balance.h
        app/account_creator.h
)

add_executable(PaymentsService ${SOURCE_FILES})

target_include_directories(PaymentsService PRIVATE ${pqxx_SOURCE_DIR}/include)
target_include_directories(PaymentsService PRIVATE ${cppkafka_SOURCE_DIR}/include)

find_path(RDKAFKA_INCLUDE_DIR NAMES librdkafka/rdkafka.h)
find_library(RDKAFKA_LIBRARY NAMES rdkafka)

target_include_directories(PaymentsService PRIVATE ${RDKAFKA_INCLUDE_DIR})
target_link_libraries(PaymentsService PRIVATE ${RDKAFKA_LIBRARY})

target_link_libraries(PaymentsService PRIVATE
        yaml-cpp
        pqxx
        OpenSSL::SSL
        OpenSSL::Crypto
        CURL::libcurl
        ${cppkafka_SOURCE_DIR}/include
        cppkafka
)