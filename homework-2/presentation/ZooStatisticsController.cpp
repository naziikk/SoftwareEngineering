#include "ZooStatisticsController.h"
#include <chrono>

void ZooStatisticsController::GetAllStatisticsRequest(const httplib::Request &request, httplib::Response &res) {

    std::vector<std::pair<int, Animal*>> animals = zoo_service.GetAllAnimals();
    std::vector<std::pair<int, Enclosure*>> enclosures = zoo_service.GetAllEnclosures();
    std::vector<FeedingSchedule> feeding_schedules = zoo_service.GetFeedingSchedules();

    json response_json;
    response_json["animals"] = json::array();

    for (const auto& [id, animal] : animals) {
        auto last_fed_time = animal->GetLastFedTime();
        auto time = std::chrono::duration_cast<std::chrono::seconds>(last_fed_time.time_since_epoch()).count();

        json animal_json = {
                {"id", id},
                {"name", animal->GetName()},
                {"birthday", animal->GetBirthday()},
                {"favorite_food", animal->GetFavoriteFood()},
                {"gender", animal->GetSex() == 0 ? "male" : "female"},
                {"status", animal->GetStatus() == 0 ? "healthy" : "sick"},
                {"last_fed_time", std::to_string(time) + " seconds ago"},
                {"type", type_map[animal->GetType()]},
                {"enclosure_id", animal->GetEnclosureId()} // не забыть про last fed time
        };
        response_json["animals"].push_back(animal_json);
    }

    response_json["enclosures"] = json::array();
    for (const auto& [id, enclosure] : enclosures) {
        json enclosure_json = {
                {"id", id},
                {"type", type_map[enclosure->GetType()]},
                {"capacity", enclosure->GetCapacity()},
                {"current_size", enclosure->GetCurrentSize()},
                {"is_full", enclosure->IsFull()},
                {"animals_in", enclosure->GetAnimalsIn()}
        };
        response_json["enclosures"].push_back(enclosure_json);
    }

    response_json["feeding_schedule"] = json::array();
    for (const auto& schedule : feeding_schedules) {
        json schedule_json = {
                {"animal_id", schedule.GetAnimalId()},
                {"feeding_interval", std::to_string(schedule.GetFeedingInterval()) + " seconds ago"},
                {"food", schedule.GetFood()}
        };
        response_json["feeding_schedule"].push_back(schedule_json);
    }

    res.status = 200;
    res.set_content(response_json.dump(), "application/json");
}