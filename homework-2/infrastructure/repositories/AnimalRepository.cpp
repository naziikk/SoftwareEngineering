#include "AnimalRepository.h"

void AnimalRepository::AddAnimal(std::unique_ptr<Animal> animal) {
    if (free_ids_.empty()) {
        animals_[current_id] = std::move(animal);
        current_id++;
    } else {
        int id = free_ids_.top();
        free_ids_.pop();
        animals_[id] = std::move(animal);
    }
}

Animal* AnimalRepository::GetAnimalById(int id) {
    auto it = animals_.find(id);

    if (it != animals_.end()) {
        return it->second.get();
    }

    return nullptr;
}

void AnimalRepository::RemoveAnimal(int id) {
    animals_.erase(id);
    free_ids_.push(id);
}

std::vector<std::pair<int, Animal*>> AnimalRepository::GetAllAnimalsInTheZoo() {
    std::vector<std::pair<int, Animal*>> animals_with_ids;
    animals_with_ids.reserve(animals_.size());

    for (const auto& [id, animal] : animals_) {
        animals_with_ids.emplace_back(id, animal.get());
    }

    return animals_with_ids;
}