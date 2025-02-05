cmake_minimum_required(VERSION 3.27)
project(homework-1)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
add_executable(homework-1 src/main.cpp
        src/Zoo.cpp)
