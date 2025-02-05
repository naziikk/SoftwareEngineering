cmake_minimum_required(VERSION 3.27)
project(homework-1)

set(CMAKE_CXX_STANDARD 17)

add_executable(homework-1 src/main.cpp
        src/Zoo.cpp)

find_package(GTest REQUIRED)
enable_testing()

add_executable(tests tests/tests.cpp
        src/Zoo.cpp)

target_link_libraries(tests GTest::GTest GTest::Main)

add_test(NAME tests COMMAND run_tests)