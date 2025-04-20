#include "FeedingSchedule.h"

bool FeedingSchedule::ShouldFeedNow() const {
    auto now = std::chrono::system_clock::now();
    return active_ && (now - last_feeding_time_ >= feeding_interval_);
}

void FeedingSchedule::MarkFed() {
    last_feeding_time_ = std::chrono::system_clock::now();
}

void FeedingSchedule::Complete() {
    active_ = false;
}

bool FeedingSchedule::IsActive() const {
    return active_;
}

int FeedingSchedule::GetAnimalId() const {
    return animal_id_;
}

const std::string& FeedingSchedule::GetFood() const {
    return food_;
}

int FeedingSchedule::GetFeedingInterval() const {
    return static_cast<int>(feeding_interval_.count());
}
