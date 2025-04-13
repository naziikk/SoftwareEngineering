#include "AnimalTransferService.h"

std::pair<bool, int> AnimalService::AddAnimal(const Animal& animal) {
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

bool AnimalService::HealAnimal(int id, std::string& message) {
    Animal* animal = animal_repository.GetAnimalById(id);

    if (!animal) {
        message = "Not Found";
        return false;
    }

//    if (!animal->Heal()) {
//        message = "Animal is already healthy";
//        return false;
//    }

    return true;
}

bool AnimalService::FeedAnimal(int id, const std::string& food, std::string& message) {
    Animal* animal = animal_repository.GetAnimalById(id);

    if (!animal) {
        message = "Not Found";
        return false;
    }

    if (!animal->Feed(food)) {
        message = "Animal don`t like this food";
        return false;
    }

    return true;
}