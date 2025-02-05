#include <iostream>
#include <vector>
#include "ZooVetClinic.h"

class Zoo {
    ZooVetClinic& vet_clinic_;
    std::vector<std::unique_ptr<Animal>> animals_;
    std::vector<std::unique_ptr<Inventory>> inventory_;
    int current_animal_inventory_number_ = 1;

public:
    explicit Zoo(ZooVetClinic& vet_clinic) : vet_clinic_(vet_clinic) {}

    void AddAnimal(std::unique_ptr<Animal> animal);

    void AddThing(std::unique_ptr<Inventory> thing);

    void ShowFoodRate();

    void ShowAnimalsInTheZoo();

    int GetAnimalsCount() const;

    int GetInventoryCount() const;

    int GetCurrentInventoryNumber() const {
        return current_animal_inventory_number_;
    }

    Animal& GetAnimalByInventoryNumber();

    Animal &GetAnimalByInventoryNumber(int inventory_number);
};

