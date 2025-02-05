#include "../include/DI-container.h"
#include <memory>
#include "../include/Zoo/Zoo.h"
#include "../include/Zoo/ZooVetClinic.h"
#include "utils.h"

int main() {
    std::string action;

    auto container = DIContainer();
    container.RegisterObject<ZooVetClinic>();
    std::shared_ptr zoo_clinic = container.GetObject<ZooVetClinic>();

    Zoo zoo(*zoo_clinic);

    ZooVetClinic clinic(*zoo_clinic);

    std::cout << "Добро пожаловать в наш зоопарк! Чего бы вы хотели?\n";
    while (true) {
        Utils::ShowMenu();
        std::cin >> action;
        if (action == "1") {
            Utils::AddAnimalInfo();
            int animal;
            std::cin >> animal;
            auto [food_rate, is_healthy] = Utils::AnimalInfo(animal);
            int kindness = 0;
            if (animal == 1 || animal == 2) {
                std::cout << "Подскажите, а на сколько добрая ваша зверюшка от 1 до 10?\n";
                std::cin >> kindness;
            }
            if (kindness != 0) {
                if (animal == 1) {
                    zoo.AddAnimal(std::make_unique<Rabbit>(food_rate, zoo.GetCurrentInventoryNumber(),
                                                           is_healthy == 1, kindness));
                } else if (animal == 2) {
                    zoo.AddAnimal(std::make_unique<Monkey>(food_rate, zoo.GetCurrentInventoryNumber(), is_healthy == 1, kindness));
                }
            } else {
                if (animal == 3) {
                    zoo.AddAnimal(std::make_unique<Wolf>(food_rate, zoo.GetCurrentInventoryNumber(), is_healthy == 1));
                } else if (animal == 4) {
                    zoo.AddAnimal(std::make_unique<Tiger>(food_rate, zoo.GetCurrentInventoryNumber(), is_healthy == 1));
                }
            }
            
        } else if (action == "2") {
            zoo.ShowFoodRate();
        } else if (action == "3") {
            zoo.ShowAnimalsInTheZoo();
        } else if (action == "4") {
            zoo.ShowAnimalsInTheZoo();
            std::cout << "Введите инвентарный номер животного, которое вы хотите вылечить\n";
            int inventory_number;
            std::cin >> inventory_number;
            clinic.TreatAnimal(zoo.GetAnimalByInventoryNumber(inventory_number));
            std::cout << "Животное успешно вылечено!\n";
        } else if (action == "5") {
            break;
        } else {
            std::cout << "Мы не можем вам помочь с таким вопросом, прочитайте документацию снова" << '\n';
        }
    }
    return 0;
}