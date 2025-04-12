#pragma once
#include <iostream>
#include "../domain/Animal.h"
#include "../infrastructure/repositories/AnimalRepository.h"
#include "../infrastructure/repositories/EnclosureRepository.h"

class AnimalService {
public:
    static std::pair<bool, int> AddAnimal(const Animal& animal);

    static bool RemoveAnimal(int id);

    bool MoveAnimal(int id, const std::string& new_enclosure);

private:
    static AnimalRepository animal_repository;
    EnclosureRepository enclosure_repository;
};

