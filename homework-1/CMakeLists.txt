cmake_minimum_required(VERSION 3.27)
project(homework-1)

set(CMAKE_CXX_STANDARD 17)

add_executable(homework-1 src/main.cpp
        src/Zoo.cpp
        src/ZooApp.cpp)

find_package(GTest REQUIRED)
enable_testing()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
add_executable(tests tests/tests.cpp
        src/Zoo.cpp)

target_link_libraries(tests GTest::GTest GTest::Main)