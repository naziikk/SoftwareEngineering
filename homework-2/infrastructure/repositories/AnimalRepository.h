#pragma once
#include <iostream>
#include <unordered_map>
#include <queue>
#include "../../domain/Animal.h"

class AnimalRepositoryInMemory {
public:
    void AddAnimal(std::unique_ptr<Animal> animal) {
        if (free_ids_.empty()) {
            animals_[std::to_string(current_id)] = std::move(animal);
            current_id++;
        } else {
            int id = free_ids_.top();
            free_ids_.pop();
            animals_[std::to_string(id)] = std::move(animal);
        }
    }

    Animal* GetAnimalById(const std::string& id) {
        auto it = animals_.find(id);
        if (it != animals_.end()) {
            return it->second.get();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Animal>> animals_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> free_ids_;
    int current_id = 0;
};

