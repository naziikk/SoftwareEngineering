#include "Animal.h"

Animal::Animal(std::string name, int status_, std::string birthday, std::string favorite_food, int type_, int sex_)
           : name(name), birthday(birthday), favorite_food(favorite_food) {
    type = type_ == 0 ? Type::Herbo : Type::Predator;
    sex = sex_ == 0 ? Sex::Male : Sex::Female;
    status = status_ == 0 ? Status::Healthy : Status::Sick;
}

std::string Animal::GetName() const {
    return name;
}

std::string Animal::GetBirthday() const {
    return birthday;
}

std::string Animal::GetFavoriteFood() const {
    return favorite_food;
}

int Animal::GetType() const {
    return type;
}

int Animal::GetSex() const {
    return sex;
}

int Animal::GetStatus() const {
    return status;
}

void Animal::SetEnclosureId(int id) {
    enclosure_id = id;
}

int Animal::GetEnclosureId() const {
    return enclosure_id;
}