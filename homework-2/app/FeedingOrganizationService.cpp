#include "FeedingOrganizationService.h"

void FeedingOrganizationService::AddFeedingSchedule(const FeedingSchedule& schedule) {
    schedules_.push_back(schedule);
}

void FeedingOrganizationService::FeedAnimals() {
    for (auto& schedule : schedules_) {
        if (!schedule.IsActive()) continue;

        if (schedule.ShouldFeedNow()) {
            Animal* animal = animal_repository_.GetAnimalById(schedule.GetAnimalId());
            if (animal && animal->Feed(schedule.GetFood())) {
                schedule.MarkFed();
            }
        }
    }
}

bool FeedingOrganizationService::CompleteFeeding(int animalId) {
    for (auto& schedule : schedules_) {
        if (schedule.GetAnimalId() == animalId && schedule.IsActive()) {
            schedule.Complete();

            return true;
        }
    }

    return false;
}

bool FeedingOrganizationService::UpdateFeedingSchedule(int animal_id, const FeedingSchedule& new_schedule) {
    for (auto& schedule : schedules_) {
        if (schedule.GetAnimalId() == animal_id) {
            schedule = new_schedule;
            return true;
        }
    }

    return false;
}