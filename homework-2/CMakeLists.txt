cmake_minimum_required(VERSION 3.10)

project(ZooApp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        infrastructure/config/config.h
        infrastructure/config/config.cpp
        infrastructure/repositories/AnimalRepository.cpp
        infrastructure/repositories/AnimalRepository.h
        infrastructure/repositories/EnclosureRepository.h
        infrastructure/repositories/EnclosureRepository.cpp
        presentation/AnimalController.cpp
        presentation/AnimalController.h
        presentation/EnclosureController.cpp
        presentation/EnclosureController.h
        presentation/FeedingScheduleController.cpp
        presentation/FeedingScheduleController.h
        presentation/ZooStatisticsController.cpp
        presentation/ZooStatisticsController.h
        domain/Animal.cpp
        domain/Animal.h
        domain/Enclosure.cpp
        domain/Enclosure.h
        domain/FeedingSchedule.cpp
        domain/FeedingSchedule.h
        app/AnimalTransferService.cpp
        app/AnimalTransferService.h
        app/FeedingOrganizationService.cpp
        app/FeedingOrganizationService.h
        app/ZooStatisticsService.h
        presentation/utils.h
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