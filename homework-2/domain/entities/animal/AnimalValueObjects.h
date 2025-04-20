#pragma once
#include <iostream>
#include <unordered_map>

class Type {
public:
    explicit Type(std::string type) {
        if (!type_map.contains(type)) {
            throw std::invalid_argument("Invalid type");
        }
        this->type = type_map[type];
    }

    int GetType() const {
        return type;
    }

    bool operator==(const Type& other) const {
        return type == other.type;
    }

private:
    std::unordered_map<std::string, int> type_map = {
            {"Herbo", 0},
            {"Predator", 1},
            {"Aquatic", 2},
            {"Bird", 3}
    };
    int type;
};


class Sex {
public:
    enum Value {
        Male = 0,
        Female = 1
    };

    explicit Sex(int val) {
        if (val != Male && val != Female) {
            throw std::invalid_argument("Invalid sex value");
        }
        value = static_cast<Value>(val);
    }

    int Get() const { return value; }

    bool operator==(const Sex& other) const {
        return value == other.value;
    }

private:
    Value value;
};

class Status {
public:
    enum Value {
        Healthy = 0,
        Sick = 1
    };

    explicit Status(int val) {
        if (val != Healthy && val != Sick) {
            throw std::invalid_argument("Invalid status value");
        }
        value = static_cast<Value>(val);
    }

    int Get() const {
        return value;
    }

    bool IsHealthy() const {
        return value == Healthy;
    }

    bool IsSick() const {
        return value == Sick;
    }

    void Heal() {
        if (value == Sick) {
            value = Healthy;
        }
    }

    bool operator==(const Status& other) const {
        return value == other.value;
    }

private:
    Value value;
};