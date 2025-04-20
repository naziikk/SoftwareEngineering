#pragma once
#include <iostream>
#include <chrono>
#include <unordered_map>
#include "AnimalValueObjects.h"

class Animal {
public:
    Animal(std::string name, int status, std::string birthday, std::string favorite_food, std::string type, int sex);

    std::string GetName() const;
    std::string GetBirthday() const;
    std::string GetFavoriteFood() const;

    int GetType() const;
    int GetSex() const;
    int GetStatus() const;

    int GetEnclosureId() const;
    void SetEnclosureId(int id);

    bool Feed(const std::string& food);
    std::chrono::system_clock::time_point GetLastFedTime() const;

    bool Heal();

private:
    std::string name;
    std::string birthday;
    std::string favorite_food;

    Status status;
    Type type;
    Sex sex;

    int enclosure_id = -1;
    std::chrono::system_clock::time_point last_fed_time_;
};

