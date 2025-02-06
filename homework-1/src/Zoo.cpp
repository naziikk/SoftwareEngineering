#include "../include/Zoo/Zoo.h"


void Zoo::AddAnimal(std::unique_ptr<Animal> animal_) {
    int id = animal_->InventoryNumber();
    std::string name = animal_->GetName();
    current_animal_inventory_number_++;

    for (const auto& animal : animals_) {
        if (animal->InventoryNumber() == id) {
            std::cout << "К сожалению, мы не можем принять это животное, "
                         "так как у нас уже есть животное с таким инвентарным номером" << '\n';
            return;
        }
    }

    if (vet_clinic_.CheckHealth(*animal_)) {
        animals_.push_back(std::move(animal_));
        std::cout << "Супер! " << name << " успешно добавлен в зоопарк" << '\n';
    } else {
        std::cout << name << " не здоров! Мы примем его, но его нужно будет вылечить..." << '\n';
        animals_.push_back(std::move(animal_));
    }
}

void Zoo::AddThing(std::unique_ptr<Inventory> thing) {
    inventory_.push_back(std::move(thing));
}

void Zoo::ShowFoodRate() {
    int total_food_rate = 0;
    for (const auto& animal : animals_) {
        std::cout << animal->GetName() << ": " << animal->GetFoodRate() << " кг еды в день" << '\n';
        total_food_rate += animal->GetFoodRate();
    }
    std::cout << "Необходимое количество еды, чтобы прокормить весь зоопарк: " << total_food_rate << " кг" << '\n';
}

void Zoo::ShowAnimalsInTheZoo() {
    std::cout << "Животные нашего зоопарка:\n";
    for (const auto& animal : animals_) {
        if (animal->GetType() == "herbo") {
            auto herbo = dynamic_cast<Herbo*>(animal.get());

            if (herbo->CanInteractWithPeople()) {
                std::cout << "Травоядное: " << animal->GetName() << ' ';

                if (!animal->IsHealthy()) {
                    std::cout << "(нуждается в лечении)" << '\n';
                } else {
                    std::cout << "(здоров)" << '\n';
                }

                std::cout << "Инвентарный номер: " << herbo->InventoryNumber() << '\n';
                std::cout << "Можно контактировать с людьми" << '\n' << '\n';
            } else {
                std::cout << "Травоядное: " << animal->GetName() << ' ';

                if (!animal->IsHealthy()) {
                    std::cout << "(нуждается в лечении)" << '\n';
                } else {
                    std::cout << "(здоров)" << '\n';
                }

                std::cout << "Инвентарный номер: " << herbo->InventoryNumber()<< '\n' << '\n';
            }
        } else {
            std::cout << "Хищник: " << animal->GetName() << ' ';

            if (!animal->IsHealthy()) {
                std::cout << "(нуждается в лечении)" << '\n';
            } else {
                std::cout << "(здоров)" << '\n';
            }

            std::cout << "Инвентарный номер: " << animal->InventoryNumber() << '\n' << '\n';
        }
    }
}

int Zoo::GetAnimalsCount() const {
    return animals_.size();
}

int Zoo::GetInventoryCount() const {
    return inventory_.size();
}

Animal& Zoo::GetAnimalByInventoryNumber(int inventory_number) {
    for (const auto& animal : animals_) {
        if (animal->InventoryNumber() == inventory_number) {
            return *animal;
        }
    }
    return *animals_[0];
}