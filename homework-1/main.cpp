#include "DI-container.h"
#include <memory>
#include "Zoo/Zoo.h"

int main() {
    auto container = DIContainer();
    container.RegisterObject<ZooVetClinic>();

    std::shared_ptr zoo_clinic = container.GetObject<ZooVetClinic>();

    Zoo zoo(*zoo_clinic);

    zoo.AddAnimal(std::make_unique<Rabbit>(7, 1, true, 6));
    zoo.AddAnimal(std::make_unique<Wolf>(25, 2, true));
    zoo.AddAnimal(std::make_unique<Monkey>(10, 3, true, 7));
    zoo.AddAnimal(std::make_unique<Tiger>(30, 4, true));

    zoo.ShowFoodRate();
    std::cout << '\n';

    zoo.ShowAnimalsInTheZoo();
    return 0;
}