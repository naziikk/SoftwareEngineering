#pragma once

#include <iostream>
#include "../infrastructure/third_party/httplib.h"
#include "../infrastructure/third_party/nlohmann/json.hpp"
#include "../app/AnimalTransferService.h"
#include "../app/FeedingOrganizationService.h"
#include "../domain/entities/FeedingSchedule.h"
#include "../infrastructure/repositories/EnclosureRepository.h"
#include "utils.h"

class FeedingScheduleController {
public:
    FeedingScheduleController(AnimalService& animal_service, AnimalRepository& animal_repository,
                               FeedingOrganizationService& feeding_service)
            : animal_service(animal_service), animal_repository(animal_repository), feeding_service(feeding_service) {}

    void AddScheduleRequest(const httplib::Request& request, httplib::Response &res);

    void UpdateScheduleRequest(const httplib::Request& request, httplib::Response &res);

    void CancelScheduleRequest(const httplib::Request& request, httplib::Response &res);

private:
    std::optional<std::tuple<int, int, std::string>> ParseAnimalFeedingInfo(const httplib::Request& request, httplib::Response& res);

private:
    using json = nlohmann::json;

    FeedingOrganizationService& feeding_service;
    AnimalRepository& animal_repository;
    AnimalService& animal_service;
};

