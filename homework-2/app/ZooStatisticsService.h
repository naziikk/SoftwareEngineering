#pragma once
#include <iostream>
#include "../domain/Animal.h"
#include "../infrastructure/repositories/AnimalRepository.h"
#include "../infrastructure/repositories/EnclosureRepository.h"

class ZooStatisticsService {
public:
    ZooStatisticsService(AnimalRepository& animal_repo, EnclosureRepository& enclosure_repo)
            : animal_repository(animal_repo), enclosure_repository(enclosure_repo) {}

    std::vector<std::pair<int, Animal*>> GetAllAnimals() {
        return animal_repository.GetAllAnimalsInTheZoo();
    }

    std::vector<std::pair<int, Enclosure*>> GetAllEnclosures() {
        return enclosure_repository.GetAllEnclosures();
    }

private:

    AnimalRepository& animal_repository;
    EnclosureRepository& enclosure_repository;
};

