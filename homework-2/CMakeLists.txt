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
        domain/entities/Animal.cpp
        domain/entities/Animal.h
        domain/entities/Enclosure.cpp
        domain/entities/Enclosure.h
        domain/entities/FeedingSchedule.cpp
        domain/entities/FeedingSchedule.h
        app/AnimalTransferService.cpp
        app/AnimalTransferService.h
        app/FeedingOrganizationService.cpp
        app/FeedingOrganizationService.h
        app/ZooStatisticsService.h
        presentation/utils.h
        domain/events/domain_event.h
        domain/events/events.h
)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(yaml-cpp)
FetchContent_MakeAvailable(spdlog)

add_executable(ZooApp ${SOURCE_FILES})

target_link_libraries(ZooApp PRIVATE
        yaml-cpp
        spdlog::spdlog
)