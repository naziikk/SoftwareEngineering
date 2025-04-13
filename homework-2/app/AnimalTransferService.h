#pragma once
#include <iostream>
#include "../domain/Animal.h"
#include "../infrastructure/repositories/AnimalRepository.h"
#include "../infrastructure/repositories/EnclosureRepository.h"

class AnimalService {
public:
    AnimalService(AnimalRepository& animal_repo, EnclosureRepository& enclosure_repo)
        : animal_repository(animal_repo), enclosure_repository(enclosure_repo) {}

    std::pair<bool, int> AddAnimal(const Animal& animal);

    bool RemoveAnimal(int id);

    bool MoveAnimal(int id, int new_enclosure_id);

    std::pair<bool, int> AddEnclosure(const Enclosure& enclosure);

    bool RemoveEnclosure(int id);

    bool HealAnimal(int id, std::string& message);

    bool FeedAnimal(int id, const std::string& food, std::string& message);

    bool CleanEnclosure(int id, std::string& message);

private:
    AnimalRepository& animal_repository;
    EnclosureRepository& enclosure_repository;
};

