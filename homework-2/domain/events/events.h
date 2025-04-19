#include "domain_event.h"
#include <spdlog/spdlog.h>
#include <chrono>

class AnimalMoveEvent : public DomainEvent {
public:
    AnimalMoveEvent(int enclosure_from, int enclosure_to, int animal_id)
            : enclosure_from(enclosure_from), enclosure_to(enclosure_to), animal_id(animal_id) {}

    std::string GetName() const override {
        return "AnimalMoveEvent";
    }

    void Print() override {
        spdlog::info("[EVENT] Animal with id {} moved from {} enclosure to {}.", animal_id, enclosure_from, enclosure_to);
    }

private:
    int enclosure_from;
    int enclosure_to;
    int animal_id;
};

class FeedingTimeEvent : public DomainEvent {
public:
    FeedingTimeEvent(int animal_id, const std::string& food)
            : animal_id(animal_id), food(food) {}

    std::string GetName() const override {
        return "FeedingTimeEvent";
    }

    void Print() override {
        std::string time = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        spdlog::info("[EVENT] Animal with id {} is fed with {}. Time: {}", animal_id, food, time);
    }
private:
    int animal_id;
    std::string food;
};