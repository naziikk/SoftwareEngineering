#pragma once

class IInventory {
public:
    virtual int InventoryNumber() const = 0;
    virtual ~IInventory() = default;
};