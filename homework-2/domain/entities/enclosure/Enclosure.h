#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "../animal/Animal.h"
#include "../animal/AnimalValueObjects.h"

class Enclosure {
public:
    Enclosure(std::string type, int capacity, int current_size = 0, bool is_full = 0);

    int GetType() const;

    int GetCapacity() const;

    bool IsFull() const;

    int GetCurrentSize() const;

    std::vector<int> GetAnimalsIn() const;

    bool AddAnimal(int animal_id);

    bool RemoveAnimal(int animal_id);

    bool CleanEnclosure();

    bool IsTimeToClean() const;

private:

    Type type;
    int capacity;
    int current_size;
    bool is_full;
    std::vector<int> animals_in_; // тут будут храниться id-шники животных
    std::chrono::system_clock::time_point last_cleaning_time_;
};
