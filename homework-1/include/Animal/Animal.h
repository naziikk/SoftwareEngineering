#pragma once
#include "../InterfaceAliveInterface.h"
#include "../InterfaceInventory.h"
#include <iostream>

class Animal : public Alive, public Inventory {
protected:
    int food_rate_;
    int inventory_number_;
    bool is_healthy_;
    std::string name_;
    std::string type_; // herbo/predator

public:
    Animal(std::string name, int food_rate, int inventory_number, bool is_healthy, std::string type)
        : name_(name), food_rate_(food_rate), inventory_number_(inventory_number),
        is_healthy_(is_healthy), type_(type){};

    int GetFoodRate() override {
        return food_rate_;
    }

    int InventoryNumber() const override {
        return inventory_number_;
    }

    bool IsHealthy() const {
        return is_healthy_;
    }

    std::string GetType() const {
        return type_;
    }
    virtual std::string GetName() const = 0;
};

class Herbo : public Animal {
protected:
    int kindness;

public:
    Herbo(std::string name, int food_rate, int inventory_number, bool is_healthy, int kindness)
        : Animal(name, food_rate, inventory_number, is_healthy, "herbo"), kindness(kindness){};

    bool CanInteractWithPeople() const {
        return kindness > 5;
    }
};

class Predator : public Animal {
public:
    Predator(std::string name, int food_rate, int inventory_number, bool is_healthy)
        : Animal(name, food_rate, inventory_number, is_healthy, "predator"){};
};

class Monkey : public Herbo {
public:
    Monkey(int food_rate, int inventory_number, bool is_healthy, int kindness)
        : Herbo("Monkey", food_rate, inventory_number, is_healthy, kindness){};

    std::string GetName() const override {
        return name_;
    }
};

class Rabbit : public Herbo {
public:
    Rabbit(int food_rate, int inventory_number, bool is_healthy, int kindness)
        : Herbo("Rabbit", food_rate, inventory_number, is_healthy, kindness){};

    std::string GetName() const override {
        return name_;
    }
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
