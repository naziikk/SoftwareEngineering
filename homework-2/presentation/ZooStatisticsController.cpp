#include "ZooStatisticsController.h"

void ZooStatisticsController::GetAllStatisticsRequest(const httplib::Request &request, httplib::Response &res) {

    std::vector<std::pair<int, Animal*>> animals = zoo_service.GetAllAnimals();
    std::vector<std::pair<int, Enclosure*>> enclosures = zoo_service.GetAllEnclosures();

    json response_json = {
            {"animals", {}}
    };

    for (const auto& [id, animal] : animals) {
        json animal_json = {
                {"id", id},
                {"name", animal->GetName()},
                {"birthday", animal->GetBirthday()},
                {"favorite_food", animal->GetFavoriteFood()},
                {"gender", animal->GetSex() == 0 ? "male" : "female"},
                {"status", animal->GetStatus() == 0 ? "healthy" : "sick"},
                {"type", type_map[animal->GetType()]},
                {"enclosure_id", animal->GetEnclosureId()} // не забыть про last fed time
        };
        response_json["animals"].push_back(animal_json);
    }

    res.status = 200;
    res.set_content(response_json.dump(), "application/json");
}