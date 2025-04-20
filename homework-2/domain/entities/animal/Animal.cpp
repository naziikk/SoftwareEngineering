#include "Animal.h"
#include "../../events/dispatcher.h"

Animal::Animal(std::string name, int status_, std::string birthday, std::string favorite_food, std::string type_, int sex_)
        : name(std::move(name)),
          birthday(std::move(birthday)),
          favorite_food(std::move(favorite_food)),
          status(status_),
          type(std::move(type_)),
          sex(sex_) {}

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
    return type.GetType();
}

int Animal::GetSex() const {
    return sex.Get();
}

int Animal::GetStatus() const {
    return status.Get();
}

void Animal::SetEnclosureId(int id) {
    enclosure_id = id;
}

int Animal::GetEnclosureId() const {
    return enclosure_id;
}

bool Animal::Heal() {
    if (!status.IsSick()) {
        return false;
    }

    status.Heal();
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