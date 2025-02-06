#include "../include/DI-container.h"
#include <memory>
#include "../include/Zoo/Zoo.h"
#include "../include/Zoo/ZooVetClinic.h"
#include "../include/utils.h"

class ZooApp {
    DIContainer container;
    std::shared_ptr<ZooVetClinic> zoo_clinic;
    std::unique_ptr<Zoo> zoo;

public:
    ZooApp() {
        container.RegisterObject<ZooVetClinic>();
        zoo_clinic = container.GetObject<ZooVetClinic>();
        zoo = std::make_unique<Zoo>(*zoo_clinic);
    }

    void Run() {
        std::cout << "Добро пожаловать в наш зоопарк! Чего бы вы хотели?\n";
        while (true) {
            Utils::ShowMenu();
            std::string action;
            std::cin >> action;

            if (action == "1") {
                AddAnimal();
            } else if (action == "2") {
                zoo->ShowFoodRate();
            } else if (action == "3") {
                zoo->ShowAnimalsInTheZoo();
            } else if (action == "4") {
                TreatAnimal();
            } else if (action == "5") {
                break;
            } else {
                std::cout << "Мы не можем вам помочь с таким вопросом, прочитайте документацию снова\n";
            }
        }
    }

private:
    void AddAnimal() {
        Utils::AddAnimalInfo();
        int animal;
        std::cin >> animal;

        auto [food_rate, is_healthy] = Utils::AnimalInfo(animal);
        auto inventory_number = zoo->GetCurrentInventoryNumber();

        if (animal == 1 || animal == 2) {
            int kindness;
            std::cout << "Подскажите, а на сколько добрая ваша зверюшка от 1 до 10?\n";
            std::cin >> kindness;

            if (animal == 1) {
                zoo->AddAnimal(std::make_unique<Rabbit>(food_rate, inventory_number, is_healthy, kindness));
            } else {
                zoo->AddAnimal(std::make_unique<Monkey>(food_rate, inventory_number, is_healthy, kindness));
            }
        } else {
            if (animal == 3) {
                zoo->AddAnimal(std::make_unique<Wolf>(food_rate, inventory_number, is_healthy));
            } else if (animal == 4) {
                zoo->AddAnimal(std::make_unique<Tiger>(food_rate, inventory_number, is_healthy));
            }
        }
    }

    void TreatAnimal() {
        zoo->ShowAnimalsInTheZoo();
        std::cout << "Введите инвентарный номер животного, которое вы хотите вылечить\n";

        int inventory_number;
        std::cin >> inventory_number;

        zoo_clinic->TreatAnimal(zoo->GetAnimalByInventoryNumber(inventory_number));
        std::cout << "Животное успешно вылечено!\n";
    }
};