#include "../InterfaceAliveInterface.h"
#include "../InterfaceInventory.h"
#include <iostream>

class Animal : public Alive, public IInventory {
protected:
    int food_rate_;
    int inventory_number_;
    bool is_healthy_;
    std::string name_;

public:
    Animal(std::string name, int food_rate, int inventory_number_, bool is_healthy)
        : name_(name), food_rate_(food_rate), inventory_number_(inventory_number_),
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

    virtual std::string GetName() const = 0;
};

class Herbo : public Animal {
protected:
    int kindness;

public:
    Herbo(std::string name, int food_rate, int inventory_number_, bool is_healthy, int kindness)
        : Animal(name, food_rate, inventory_number_, is_healthy), kindness(kindness){};

    bool СanInteract() {
        return kindness > 5;
    }
};

class Predator : public Animal {
public:
    Predator(std::string name, int food_rate, int inventory_number_, bool is_healthy)
        : Animal(name, food_rate, inventory_number_, is_healthy){};
};

class Monkey : public Herbo {
public:
    Monkey(int food_rate, int inventory_number_, bool is_healthy, int kindness)
        : Herbo("Monkey", food_rate, inventory_number_, is_healthy, kindness){};

    std::string GetName() const override {
        return name_;
    }
};

class Rabbit : public Herbo {
public:
    Rabbit(int food_rate, int inventory_number, bool is_healthy, int kindness)
        : Herbo("Rabbit", food_rate, inventory_number, is_healthy, kindness){};
};

class Wolf : public Predator {
public:
    Wolf(int food_rate, int inventory_number, bool is_healthy)
        : Predator("Wolf", food_rate, inventory_number, is_healthy){};

    std::string GetName() const override {
        return name_;
    }
};

class Tiger : public Predator {
public:
    Tiger(int food_rate, int inventory_number, bool is_healthy)
        : Predator("Tiger", food_rate, inventory_number, is_healthy){};

    std::string GetName() const override {
        return name_;
    }
};
