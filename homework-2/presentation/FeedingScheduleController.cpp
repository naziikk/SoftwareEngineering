#include "FeedingScheduleController.h"

std::pair<bool, int> GetAnimalId(const httplib::Request& request, httplib::Response& res) {
    int id;
    if (!request.path_params.at("id").empty()) {
        id = std::stoi(request.path_params.at("id"));
    } else {
        SendError(res, 400, "Missing animal id parameter");
        return {false, -1};
    }

    return {true, id};
}

std::optional<std::tuple<int, int, std::string>> FeedingScheduleController::ParseAnimalFeedingInfo(const httplib::Request& request, httplib::Response& res) {
    auto [ok, animal_id] = GetAnimalId(request, res);
    if (!ok) {
        return std::nullopt;
    }

    auto parsed = json::parse(request.body);

    int interval = parsed.at("interval").get<int>();

    Animal* animal = animal_repository.GetAnimalById(animal_id);
    if (!animal) {
        SendError(res, 404, "Animal not found");
        return std::nullopt;
    }

    std::string food = animal->GetFavoriteFood();

    return std::make_tuple(animal_id, interval, food);
}

void FeedingScheduleController::AddScheduleRequest(const httplib::Request& request, httplib::Response &res) {
    auto info = ParseAnimalFeedingInfo(request, res);
    if (!info) {
        return;
    }

    auto [animal_id, interval, food] = *info;

    feeding_service.AddFeedingSchedule(FeedingSchedule(animal_id, std::chrono::seconds(interval), food));

    res.status = 201;
    res.set_content(R"({"message": "Feeding schedule added successfully"})", "application/json");
}

void FeedingScheduleController::UpdateScheduleRequest(const httplib::Request& request, httplib::Response &res) {
    auto info = ParseAnimalFeedingInfo(request, res);
    if (!info) {
        return;
    }

    auto [animal_id, interval, food] = *info;

    FeedingSchedule new_schedule(animal_id, std::chrono::seconds(interval), food);

    bool updated = feeding_service.UpdateFeedingSchedule(animal_id, new_schedule);

    if (updated) {
        res.status = 200;
        res.set_content(R"({"message": "Feeding schedule updated successfully"})", "application/json");
    } else {
        SendError(res, 404, "Feeding schedule not found for this animal");
    }
}

void FeedingScheduleController::CancelScheduleRequest(const httplib::Request& request, httplib::Response &res) {
    std::pair<bool, int> response = GetAnimalId(request, res);

    if (!response.first) {
        return;
    }

    int animal_id = response.second;

    Animal* animal = animal_repository.GetAnimalById(animal_id);

    if (!animal) {
        SendError(res, 404, "Animal not found");
        return;
    }

    bool completed = feeding_service.CompleteFeeding(animal_id);

    if (!completed) {
        SendError(res, 404, "Feeding schedule not found for this animal");
        return;
    }

    res.status = 200;
    res.set_content(R"({"message": "Feeding schedule completed successfully"})", "application/json");
}