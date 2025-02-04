#include "../InterfaceAliveInterface.h"
#include "../InterfaceInventory.h"

class Animal : public Alive, public IInventory {
protected:
    int food_rate_;
    int inventory_number_;
    bool is_healthy_;

public:
    Animal(int food_rate, int inventory_number_, bool is_healthy)
        : food_rate_(food_rate), inventory_number_(inventory_number_),
        is_healthy_(is_healthy){};

    int GetFoodRate() override {
        return food_rate_;
    }

    int InventoryNumber() const override {
        return inventory_number_;
    }

    bool IsHealthy() const {
        return is_healthy_;
    }
};

class Herbo : public Animal {
protected:
    int kindness;

public:
    Herbo(int food_rate, int inventory_number_, bool is_healthy, int kindness)
        : Animal(food_rate, inventory_number_, is_healthy), kindness(kindness){};

    bool СanInteract() {
        return kindness > 5;
    }
};

class Predator : public Animal {
public:
    Predator(int food_rate, int inventory_number_, bool is_healthy)
        : Animal(food_rate, inventory_number_, is_healthy){};
};
