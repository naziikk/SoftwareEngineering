#include "AnimalController.h"

Animal AnimalController::GetAnimal(const json& parsed) {
    return Animal(parsed.at("name").get<std::string>(),
                                parsed.at("health_status").get<int>(),
                                parsed.at("birthday").get<std::string>(),
                                parsed.at("favorite_food").get<std::string>(),
                                parsed.at("type").get<std::string>(),
                                parsed.at("sex").get<int>());
}

std::pair<bool, int> GetId(const httplib::Request& request, httplib::Response& res) {
    int id;
    if (!request.path_params.at("id").empty()) {
        id = std::stoi(request.path_params.at("id"));
    } else {
        SendError(res, 400, "Missing animal id parameter");
        return {false, -1};
    }

    return {true, id};
}

void AnimalController::AddAnimal(const httplib::Request& request, httplib::Response &res) {
    auto parsed = json::parse(request.body);
    Animal to_add = GetAnimal(parsed);

    std::pair<bool, int> response = animal_service.AddAnimal(to_add);
    if (!response.first) {
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
    std::pair<bool, int> response = GetId(request, res);

    if (!response.first) {
        return;
    }

    int animal_id = response.second;

    enclosure_repository.RemoveAnimal(animal_id);

    if (!animal_service.RemoveAnimal(animal_id)) {
        SendError(res, 409, "Animal not found");
        return;
    }

    json response_json = {
            {"message", "Animal successfully deleted"}
    };
    res.status = 200;
    res.set_content(response_json.dump(), "application/json");
}

void AnimalController::MoveAnimal(const httplib::Request& request, httplib::Response &res) {
    std::pair<bool, int> response = GetId(request, res);

    if (!response.first) {
        return;
    }

    int animal_id = response.second;

    auto parsed = json::parse(request.body);
    int new_enclosure_id = parsed.at("enclosure_id").get<int>();

    if (!animal_service.MoveAnimal(animal_id, new_enclosure_id)) {
        SendError(res, 409, "Animal not found or enclosure is full");
        return;
    }

    res.status = 200;
    json response_json = {
            {"message", "Animal successfully moved"},
            {"animal_id", animal_id},
            {"new_enclosure_id", new_enclosure_id}
    };
    res.set_content(response_json.dump(), "application/json");
}

void AnimalController::HealAnimal(const httplib::Request& request, httplib::Response &res) {
    std::pair<bool, int> response = GetId(request, res);

    if (!response.first) {
        return;
    }

    int animal_id = response.second;

    std::string message;
    if (!animal_service.HealAnimal(animal_id, message)) {
        if (message == "Not found") {
            SendError(res, 404, message);
            return;
        } else {
            SendError(res, 400, message);
            return;
        }
    }

    res.status = 200;
    json response_json = {
            {"message", "Animal successfully healed"},
            {"animal_id", animal_id}
    };
    res.set_content(response_json.dump(), "application/json");
}

void AnimalController::FeedAnimal(const httplib::Request& request, httplib::Response &res) {
    std::pair<bool, int> response = GetId(request, res);

    if (!response.first) {
        return;
    }

    int animal_id = response.second;
    std::string food = json::parse(request.body).at("food").get<std::string>();

    std::string message;
    if (!animal_service.FeedAnimal(animal_id, food, message)) {
        if (message == "Not found") {
            SendError(res, 404, message);
            return;
        } else {
            SendError(res, 400, message);
            return;
        }
    }

    res.status = 200;
    json response_json = {
            {"message", "Animal successfully fed"},
            {"animal_id", animal_id},
            {"food", food}
    };
    res.set_content(response_json.dump(), "application/json");
}