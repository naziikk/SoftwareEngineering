#pragma once
#include <iostream>
#include "../domain/Animal.h"
#include "../infrastructure/repositories/AnimalRepository.h"
#include "../infrastructure/repositories/EnclosureRepository.h"

class AnimalService {
public:
    bool AddAnimal(const Animal& animal);

    bool RemoveAnimal(int id);

    bool MoveAnimal(int id, const std::string& new_enclosure);

private:
    AnimalRepository animal_repository;
    EnclosureRepository enclosure_repository;
};

