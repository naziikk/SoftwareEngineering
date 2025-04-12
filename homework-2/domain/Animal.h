#pragma once
#include <iostream>
#include <unordered_map>

class Animal {
public:
    Animal() = default;

    Animal(std::string name, int status, std::string birthday, std::string favorite_food, std::string type, int sex);

    std::string GetName() const;

    std::string GetHabitat() const;

    std::string GetBirthday() const;

    std::string GetFavoriteFood() const;

    int GetType() const;

    int GetSex() const;

    int GetStatus() const;

    int GetEnclosureId() const;

    void SetEnclosureId(int id);

private:
    enum Sex {
        Male = 0,
        Female = 1
    };

    enum Status {
        Healthy = 0,
        Sick = 1
    };

private:
    std::unordered_map<std::string, int> type_map = {
            {"Herbo", 0},
            {"Predator", 1},
            {"Aquatic", 2},
            {"Bird", 3}
    };

    std::string name;
    std::string birthday;
    std::string favorite_food;

    Status status;
    int type;
    Sex sex;

    int enclosure_id = -1;
};

