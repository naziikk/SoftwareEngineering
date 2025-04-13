#pragma once
#include <iostream>
#include "../infrastructure/third_party/httplib.h"
#include "../infrastructure/third_party/nlohmann/json.hpp"
#include "../app/AnimalTransferService.h"
#include "../infrastructure/repositories/EnclosureRepository.h"
#include "utils.h"

class EnclosureController {
public:
    EnclosureController(AnimalService& animal_service, AnimalRepository& animal_repository)
        : animal_service(animal_service), animal_repository(animal_repository) {}

    void AddEnclosure(const httplib::Request& request, httplib::Response &res);

    void RemoveEnclosure(const httplib::Request& request, httplib::Response &res);

private:
    static Enclosure GetEnclosure(const nlohmann::json& parsed);

private:
    using json = nlohmann::json;

    AnimalService& animal_service;
    AnimalRepository& animal_repository;
};
