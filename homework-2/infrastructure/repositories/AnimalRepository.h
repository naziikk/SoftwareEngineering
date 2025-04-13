#pragma once
#include <iostream>
#include <unordered_map>
#include <queue>
#include "../../domain/Animal.h"

class AnimalRepository {
public:
    int AddAnimal(std::unique_ptr<Animal> animal);

    bool RemoveAnimal(int id);

    Animal* GetAnimalById(int id);

    std::vector<std::pair<int, Animal*>> GetAllAnimalsInTheZoo();

    void SetEnclosureToUndefinedAfterRemovingEnclosure(int id);

private:
    std::unordered_map<int, std::unique_ptr<Animal>> animals_;
    std::priority_queue<int, std::vector<int>, std::greater<>> free_ids_;
    int current_id = 0;
};

