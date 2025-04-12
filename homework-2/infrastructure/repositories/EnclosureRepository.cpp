#include "EnclosureRepository.h"

void EnclosureRepository::AddEnclosure(std::unique_ptr<Enclosure> animal) {
    if (free_ids_.empty()) {
        enclosures_[current_id] = std::move(animal);
        current_id++;
    } else {
        int id = free_ids_.top();
        free_ids_.pop();
        enclosures_[id] = std::move(animal);
    }
}

Enclosure* EnclosureRepository::GetEnclosureById(int id) {
    auto it = enclosures_.find(id);
    if (it != enclosures_.end()) {
        return it->second.get();
    }
    return nullptr;
}

void EnclosureRepository::RemoveEnclosure(int id) {
    enclosures_.erase(id);
    free_ids_.push(id);
}

std::vector<std::pair<int, Enclosure*>> EnclosureRepository::GetAllEnclosures() {
    std::vector<std::pair<int, Enclosure*>> enclosures_with_ids;

    for (const auto& [id, enclosure] : enclosures_) {
        enclosures_with_ids.emplace_back(id, enclosure.get());
    }

    return enclosures_with_ids;
}