#include "EnclosureRepository.h"
#include "../../domain/events/dispatcher.h"

int EnclosureRepository::AddEnclosure(std::unique_ptr<Enclosure> animal) {
    if (free_ids_.empty()) {
        enclosures_[current_id] = std::move(animal);
        current_id++;
    } else {
        int id = free_ids_.top();
        free_ids_.pop();
        enclosures_[id] = std::move(animal);

        return id;
    }

    return current_id - 1;
}

Enclosure* EnclosureRepository::GetEnclosureById(int id) {
    auto it = enclosures_.find(id);
    if (it != enclosures_.end()) {
        return it->second.get();
    }
    return nullptr;
}

bool EnclosureRepository::RemoveEnclosure(int id) {
    if (!enclosures_.contains(id)) {
        return false;
    }

    enclosures_.erase(id);
    free_ids_.push(id);

    return true;
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

    Animal* animal = animal_repository_.GetAnimalById(animal_id);
    int old_enclosure_id = -1;

    if (animal) {
        old_enclosure_id = animal->GetEnclosureId();
        if (animal->GetType() != enclosure->GetType()) {
            return false; // that means that this type of animal can't be in this enclosure (types are different)
        }
    }

    if (old_enclosure_id != -1) {
        std::cout << "3" << std::endl;
        Enclosure* old_enclosure = GetEnclosureById(old_enclosure_id);

        AnimalMoveEvent event(old_enclosure_id, enclosure_id, animal_id);
        EventDispatcher::Dispatch(event);

        old_enclosure->RemoveAnimal(animal_id);
    } else {
        AnimalMoveEvent event(-1, enclosure_id, animal_id);
        EventDispatcher::Dispatch(event);
    }

    enclosure->AddAnimal(animal_id);
    animal_repository_.GetAnimalById(animal_id)->SetEnclosureId(enclosure_id);

    return true;
}

bool EnclosureRepository::RemoveAnimal(int animal_id) {
    Animal* animal = animal_repository_.GetAnimalById(animal_id);

    if (!animal) {
        return false;
    }

    int old_enclosure_id = animal->GetEnclosureId();

    if (old_enclosure_id != -1) {
        Enclosure* old_enclosure = GetEnclosureById(old_enclosure_id);

        if (!old_enclosure->RemoveAnimal(animal_id)) {
            return false;
        }
    }

    return true;
}