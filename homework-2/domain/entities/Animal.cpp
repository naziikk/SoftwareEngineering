#include "Animal.h"
#include "../events/dispatcher.h"

Animal::Animal(std::string name, int status_, std::string birthday, std::string favorite_food, std::string type_, int sex_)
           : name(name), birthday(birthday), favorite_food(favorite_food) {
    type = type_map[type_];
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

bool Animal::Heal() {
    if (status != Status::Sick) {
        return false;
    }

    status = Status::Healthy;
    return true;
}

std::chrono::system_clock::time_point Animal::GetLastFedTime() const {
    return last_fed_time_;
}

bool Animal::Feed(const std::string& food) {
    if (food == favorite_food) {
        FeedingTimeEvent event(enclosure_id, food);
        EventDispatcher::Dispatch(event);
        last_fed_time_ = std::chrono::system_clock::now();

        return true;
    }

    return false;
}