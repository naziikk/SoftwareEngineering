cmake_minimum_required(VERSION 3.5)

project(ZooApp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
    main.cpp
    infrastructure/config/config.h
    infrastructure/config/config.cpp
    infrastructure/config/config.yaml
    infrastructure/repositories/AnimalRepository.cpp
    infrastructure/repositories/AnimalRepository.h
    infrastructure/repositories/EnclosureRepository.h
    infrastructure/repositories/EnclosureRepository.cpp
)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
)
FetchContent_MakeAvailable(yaml-cpp)


add_executable(ZooApp ${SOURCE_FILES})

target_link_libraries(ZooApp PRIVATE
        yaml-cpp
)