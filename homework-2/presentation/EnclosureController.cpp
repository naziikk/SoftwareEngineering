#include "EnclosureController.h"
Enclosure EnclosureController::GetEnclosure(const nlohmann::json &parsed) {
    return Enclosure(parsed["type"], parsed["capacity"]);
}

void EnclosureController::AddEnclosure(const httplib::Request& request, httplib::Response &res) {
    auto parsed = json::parse(request.body);

    Enclosure new_enclosure = GetEnclosure(parsed);

    std::pair<bool, int> response = animal_service.AddEnclosure(new_enclosure);

    if (!response.first) {
        SendError(res, 400, "Enclosure is not valid");
        return;
    }

    res.status = 200;
    json response_json = {
            {"message", "Enclosure successfully added"},
            {"id", response.second}
    };
    res.set_content(response_json.dump(), "application/json");
}

void EnclosureController::RemoveEnclosure(const httplib::Request& request, httplib::Response &res) {
    int enclosure_id;
    if (!request.path_params.at("id").empty()) {
        enclosure_id = std::stoi(request.path_params.at("id"));
    } else {
        SendError(res, 400, "Missing enclosure id parameter");
        return;
    }

    if (!animal_service.RemoveEnclosure(enclosure_id)) {
        SendError(res, 404, "Enclosure not found");
        return;
    }

    animal_repository.SetEnclosureToUndefinedAfterRemovingEnclosure(enclosure_id); // define that all animals now need a new enclosure

    json response_json = {
            {"message", "Enclosure successfully deleted"}
    };
    res.status = 200;
    res.set_content(response_json.dump(), "application/json");
}