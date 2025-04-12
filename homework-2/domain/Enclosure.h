#pragma once
#include <iostream>
#include <unordered_map>

class Enclosure {
    std::unordered_map<std::string, int> type_map = {
            {"Herbo", 0},
            {"Predator", 1},
            {"Aquatic", 2},
            {"Birds", 3}
    };

public:
    Enclosure(std::string type, int capacity, int current_size = 0, bool is_full = 0);

    int GetType() const;

    int GetCapacity() const;

    bool IsFull() const;

    int GetCurrentSize() const;

private:
    int type;
    int capacity;
    int current_size;
    bool is_full;
};
