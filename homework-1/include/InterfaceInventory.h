#pragma once

class Inventory {
public:
    virtual int InventoryNumber() const = 0;
    virtual ~Inventory() = default;
};