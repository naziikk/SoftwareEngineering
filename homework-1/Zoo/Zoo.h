#include <iostream>
#include <vector>
#include "ZooVetClinic.h"

class Zoo {
private:
    ZooVetClinic& vet_clinic_;
    std::vector<std::unique_ptr<Animal>> animals_;
    std::vector<std::unique_ptr<Inventory>> inventory_;

public:
    explicit Zoo(ZooVetClinic& vet_clinic) : vet_clinic_(vet_clinic) {}

    void AddAnimal(std::unique_ptr<Animal> animal) {
        if (vet_clinic_.CheckHealth(*animal)) {
            animals_.push_back(std::move(animal));
        } else {
            std::cout << animal->GetName() << " не здоров! К сожалению мы не можем его принять" << '\n';
        }
    }

    void AddThing(std::unique_ptr<Inventory> thing) {
        inventory_.push_back(std::move(thing));
    }

    void ShowFoodRate() {
        int total_food_rate = 0;
        for (const auto& animal : animals_) {
            std::cout << animal->GetName() << ": " << animal->GetFoodRate() << " кг еды в день" << '\n';
            total_food_rate += animal->GetFoodRate();
        }
        std::cout << "Необходимое количество еды, чтобы прокормить весь зоопарк: " << total_food_rate << " кг" << '\n';
    }

    void ShowAnimalsInTheZoo() {
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
};

