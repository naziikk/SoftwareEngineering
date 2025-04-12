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

bool AnimalService::MoveAnimal(int id, const std::string& new_enclosure) {
    if (!enclosure_repository.MoveAnimalToEnclosure(id, std::stoi(new_enclosure))) {
        return false;
    }

    return true;
}