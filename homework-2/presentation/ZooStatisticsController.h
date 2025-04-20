#pragma once
#include "../infrastructure/third_party/nlohmann/json.hpp"
#include "../infrastructure/third_party/httplib.h"
#include "../app/ZooStatisticsService.h"
#include "../domain/entities/animal/Animal.h"
#include "utils.h"
#include <iostream>

class ZooStatisticsController {
public:
    ZooStatisticsController(ZooStatisticsService& zoo_service)
            : zoo_service(zoo_service) {}

    void GetAllStatisticsRequest(const httplib::Request& request, httplib::Response &res);

private:
    std::unordered_map<int, std::string> type_map = {
            {0, "Herbo"},
            {1, "Predator"},
            {2, "Aquatic"},
            {3, "Bird"}
    };

    using json = nlohmann::json;

    ZooStatisticsService& zoo_service;
};

