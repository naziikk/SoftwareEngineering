#pragma once
#include <iostream>

class Animal {
public:
    Animal() = default;

    Animal(std::string name, int status, std::string birthday, std::string favorite_food, int type, int sex);

    std::string GetName() const;

    std::string GetHabitat() const;

    std::string GetBirthday() const;

    std::string GetFavoriteFood() const;

    int GetType() const;

    int GetSex() const;

    int GetStatus() const;

private:
    enum Sex {
        Male = 0,
        Female = 1
    };

    enum Type {
        Herbo = 0,
        Predator
    };

    enum Status {
        Healthy = 0,
        Sick = 1
    };

private:
    std::string name;
    std::string birthday;
    std::string favorite_food;

    Status status;
    Type type;
    Sex sex;
};

