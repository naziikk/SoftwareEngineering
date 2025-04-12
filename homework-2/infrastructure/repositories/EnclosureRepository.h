#pragma once
#include <iostream>
#include <queue>
#include "../../domain/Enclosure.h"
#include "AnimalRepository.h"

class EnclosureRepository {
public:
    void AddEnclosure(std::unique_ptr<Enclosure> animal);

    void RemoveEnclosure(int id);

    std::vector<std::pair<int, Enclosure*>> GetAllEnclosures();

    Enclosure* GetEnclosureById(int id);

    bool MoveAnimalToEnclosure(int animal_id, int enclosure_id);

private:
    std::unordered_map<int, std::unique_ptr<Enclosure>> enclosures_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> free_ids_;
    int current_id = 0;

    AnimalRepository animal_repository_;
};
