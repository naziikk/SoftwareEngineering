#pragma once
#include <iostream>
#include <queue>
#include "../../domain/Enclosure.h"

class EnclosureRepository {
public:
    void AddEnclosure(std::unique_ptr<Enclosure> animal);

    void RemoveEnclosure(int id);

    std::vector<std::pair<int, Enclosure*>> GetAllEnclosures();

    Enclosure* GetEnclosureById(int id);

private:
    std::unordered_map<int, std::unique_ptr<Enclosure>> enclosures_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> free_ids_;
    int current_id = 0;
};
