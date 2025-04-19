#pragma once
#include <iostream>
#include <chrono>
#include <string>

class FeedingSchedule {
public:
    FeedingSchedule(int animalId, std::chrono::seconds interval, std::string& food)
            : animal_id_(animalId),
              feeding_interval_(interval),
              food_(food),
              last_feeding_time_(std::chrono::system_clock::now()),
              active_(true) {}

    bool ShouldFeedNow() const;

    void MarkFed();

    void Complete();

    bool IsActive() const;

    int GetAnimalId() const;

    const std::string& GetFood() const;

    int GetFeedingInterval() const;

private:
    int animal_id_;
    std::chrono::seconds feeding_interval_;
    std::string food_;
    std::chrono::system_clock::time_point last_feeding_time_;
    bool active_;
};