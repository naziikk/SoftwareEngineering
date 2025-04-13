#pragma once

#include <vector>
#include "../domain/FeedingSchedule.h"
#include "../domain/Animal.h"
#include "../infrastructure/repositories/AnimalRepository.h"

class FeedingOrganizationService {
public:
    explicit FeedingOrganizationService(AnimalRepository& animal_repository)
            : animal_repository_(animal_repository) {}

    void AddFeedingSchedule(const FeedingSchedule& schedule);

    bool UpdateFeedingSchedule(int animal_id, const FeedingSchedule& new_schedule);

    void FeedAnimals();

    bool CompleteFeeding(int animalId);

    std::vector<FeedingSchedule> GetFeedingSchedules() const {
        return schedules_;
    }

private:
    AnimalRepository& animal_repository_;
    std::vector<FeedingSchedule> schedules_;
};