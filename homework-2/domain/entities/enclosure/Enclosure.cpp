#include "Enclosure.h"

Enclosure::Enclosure(std::string type_, int capacity, int current_size, bool is_full)
    : capacity(capacity), current_size(0), is_full(0), type(std::move(type_)) {}

int Enclosure::GetType() const {
    return type.GetType();
}

int Enclosure::GetCapacity() const {
    return capacity;
}

bool Enclosure::IsFull() const {
    return is_full;
}

int Enclosure::GetCurrentSize() const {
    return current_size;
}

std::vector<int> Enclosure::GetAnimalsIn() const {
    return animals_in_;
}

bool Enclosure::AddAnimal(int animal_id) {
    if (current_size < capacity) {
        animals_in_.push_back(animal_id);
        current_size++;
        if (current_size == capacity) {
            is_full = true;
        }
        return true;
    }
    return false;
}

bool Enclosure::RemoveAnimal(int animal_id) {
    auto it = std::find(animals_in_.begin(), animals_in_.end(), animal_id);
    if (it != animals_in_.end()) {
        animals_in_.erase(it);
        current_size--;
        is_full = false;

        return true;
    }

    return false;
}

bool Enclosure::CleanEnclosure() {
    if (IsTimeToClean()) {
        last_cleaning_time_ = std::chrono::system_clock::now();
        return true;
    }

    return false;
}

bool Enclosure::IsTimeToClean() const {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(now - last_cleaning_time_);

    return duration.count() >= 1;
}