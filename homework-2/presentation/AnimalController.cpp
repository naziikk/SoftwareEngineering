#include "AnimalController.h"

Animal AnimalController::GetAnimal(const json& parsed) {
    return Animal(parsed.at("name").get<std::string>(),
                                parsed.at("health_status").get<int>(),
                                parsed.at("birthday").get<std::string>(),
                                parsed.at("favorite_food").get<std::string>(),
                                parsed.at("type").get<std::string>(),
                                parsed.at("sex").get<int>());
}

void AnimalController::AddAnimal(const httplib::Request& request, httplib::Response &res) {
    auto parsed = json::parse(request.body);
    Animal to_add = GetAnimal(parsed);

    std::pair<bool, int> response = AnimalService::AddAnimal(to_add);
    if (response.first) {
        SendError(res, 400, "Your animal is not healthy");
        return;
    }

    res.status = 200;
    json response_json = {
            {"message", "Animal successfully added"},
            {"id", response.second}
    };
    res.set_content(response_json.dump(), "application/json");
}

void AnimalController::RemoveAnimal(const httplib::Request& request, httplib::Response &res) {
    int animal_id;
    if (!request.path_params.at("id").empty()) {
        animal_id = std::stoi(request.path_params.at("id"));
    } else {
        SendError(res, 400, "Missing animal id parameter");
        return;
    }

    if (!AnimalService::RemoveAnimal(animal_id)) {
        SendError(res, 404, "Animal not found");
        return;
    }

    EnclosureRepository::RemoveAnimal(animal_id);

    res.status = 200;
    res.set_content("Animal successfully deleted", "application/json");
}

void AnimalController::MoveAnimal(const httplib::Request& request, httplib::Response &res) {

}