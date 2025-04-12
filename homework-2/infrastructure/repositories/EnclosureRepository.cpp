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

    enclosures_with_ids.reserve(enclosures_.size());

    for (const auto& [id, enclosure] : enclosures_) {
        enclosures_with_ids.emplace_back(id, enclosure.get());
    }

    return enclosures_with_ids;
}

bool EnclosureRepository::MoveAnimalToEnclosure(int animal_id, int enclosure_id) {
    if (!enclosures_.contains(enclosure_id)) {
        return false;
    }

    if (!animal_repository_.GetAnimalById(animal_id)) {
        return false;
    }

    Enclosure* enclosure = GetEnclosureById(enclosure_id);

    if (enclosure->IsFull()) {
        return false;
    }

    int old_enclosure_id = animal_repository_.GetAnimalById(animal_id)->GetEnclosureId();

    if (old_enclosure_id != -1) {
        Enclosure* old_enclosure = GetEnclosureById(old_enclosure_id);

        old_enclosure->RemoveAnimal(animal_id);
    }

    enclosure->AddAnimal(animal_id);
    animal_repository_.GetAnimalById(animal_id)->SetEnclosureId(enclosure_id);

    return true;
}

void EnclosureRepository::RemoveAnimal(int animal_id) {
    int old_enclosure_id = animal_repository_.GetAnimalById(animal_id)->GetEnclosureId();

    if (old_enclosure_id != -1) {
        Enclosure* old_enclosure = GetEnclosureById(old_enclosure_id);

        old_enclosure->RemoveAnimal(animal_id);
    }
}