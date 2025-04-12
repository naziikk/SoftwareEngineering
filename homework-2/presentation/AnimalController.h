#pragma once
#include "../infrastructure/third_party/nlohmann/json.hpp"
#include "../infrastructure/third_party/httplib.h"
#include "../app/AnimalTransferService.h"
#include "../domain/Animal.h"
#include "utils.h"
#include <iostream>

class AnimalController {
public:
    AnimalController(AnimalService& animal_service, EnclosureRepository& enclosure_repository)
        : animal_service(animal_service), enclosure_repository(enclosure_repository) {}

    void AddAnimal(const httplib::Request& request, httplib::Response &res);

    void RemoveAnimal(const httplib::Request& request, httplib::Response &res);

    static void MoveAnimal(const httplib::Request& request, httplib::Response &res);

private:
    static Animal GetAnimal(const nlohmann::json & parsed);

private:
    using json = nlohmann::json;

    AnimalService& animal_service;
    EnclosureRepository& enclosure_repository;
};

