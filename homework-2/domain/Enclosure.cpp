#include "Enclosure.h"

Enclosure::Enclosure(std::string type_, int capacity, int current_size, bool is_full)
    : capacity(capacity), current_size(0), is_full(0) {
    type = type_map[type_];
}

int Enclosure::GetType() const {
    return type;
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