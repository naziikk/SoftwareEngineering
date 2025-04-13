#include "AnimalTransferService.h"

std::pair<bool, int> AnimalService::AddAnimal(const Animal& animal) {
    if (animal.GetStatus() == 1) {
        return {false, -1};
    }

    int id = animal_repository.AddAnimal(std::make_unique<Animal>(animal));

    return {true, id};
}

bool AnimalService::RemoveAnimal(int id) {
    if (!animal_repository.RemoveAnimal(id)) {
        return false;
    }

    return true;
}

bool AnimalService::MoveAnimal(int id, int new_enclosure_id) {
    if (!enclosure_repository.MoveAnimalToEnclosure(id, new_enclosure_id)) {
        return false;
    }

    return true;
}

std::pair<bool, int> AnimalService::AddEnclosure(const Enclosure& enclosure) {
    int id = enclosure_repository.AddEnclosure(std::make_unique<Enclosure>(enclosure));

    return {true, id};
}

bool AnimalService::RemoveEnclosure(int id) {
    if (!enclosure_repository.RemoveEnclosure(id)) {
        return false;
    }

    return true;
}