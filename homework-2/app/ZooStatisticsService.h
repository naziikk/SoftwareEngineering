#pragma once
#include <iostream>
#include "../domain/entities/Animal.h"
#include "../infrastructure/repositories/AnimalRepository.h"
#include "../infrastructure/repositories/EnclosureRepository.h"
#include "../app/FeedingOrganizationService.h"

class ZooStatisticsService {
public:
    ZooStatisticsService(AnimalRepository& animal_repo, EnclosureRepository& enclosure_repo, FeedingOrganizationService& feeding_service)
            : animal_repository(animal_repo), enclosure_repository(enclosure_repo), feeding_service(feeding_service) {}

    std::vector<std::pair<int, Animal*>> GetAllAnimals() {
        return animal_repository.GetAllAnimalsInTheZoo();
    }

    std::vector<std::pair<int, Enclosure*>> GetAllEnclosures() {
        return enclosure_repository.GetAllEnclosures();
    }

    std::vector<FeedingSchedule> GetFeedingSchedules() {
        return feeding_service.GetFeedingSchedules();
    }

private:
    FeedingOrganizationService& feeding_service;
    AnimalRepository& animal_repository;
    EnclosureRepository& enclosure_repository;
};

