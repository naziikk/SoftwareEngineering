#include "../include/Zoo/Zoo.h"


void Zoo::AddAnimal(std::unique_ptr<Animal> animal) {
    if (vet_clinic_.CheckHealth(*animal)) {
        animals_.push_back(std::move(animal));
    } else {
        std::cout << animal->GetName() << " не здоров! К сожалению мы не можем его принять" << '\n';
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
    for (const auto& animal : animals_) {
        if (animal->GetType() == "herbo") {
            auto herbo = dynamic_cast<Herbo*>(animal.get());
            if (herbo->СanInteractWithPeople()) {
                std::cout << "Травоядное: " << animal->GetName() << ". Можно контактировать с людьми" << '\n';
            } else {
                std::cout << "Травоядное: " << animal->GetName() << '\n';
            }
        } else {
            std::cout << "Хищник: " << animal->GetName() << '\n';
        }
    }
}

