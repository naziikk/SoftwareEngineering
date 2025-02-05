#include "../InterfaceInventory.h"
#include <iostream>

class Thing : public IInventory {
protected:
    std::string name_;
    int inventory_number_;

public:
    Thing(std::string name, int inventory_number)
        : name_(name), inventory_number_(inventory_number){};

    int InventoryNumber() const override {
        return inventory_number_;
    }

    std::string GetName() const {
        return name_;
    }
};

class Table : public Thing {
protected:
    int inventory_number_;
    std::string name_;

public:
    Table(std::string& name, int inventory_number)
        : Thing("Table", inventory_number){};
};

class Computer : public Thing {
protected:
    int inventory_number_;
    std::string name_;

public:
    Computer(int inventory_number)
        : Thing("Computer", inventory_number){};
};