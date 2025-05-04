#include <iostream>
#include <vector>
#include <string>
#include "../third_party/nlohmann/nlohmann.hpp"
#include "../third_party/httplib.h"

std::string extract_id_from_request(const httplib::Request& req) {
    if (!req.path_param.at("id").empty()) {
        return req.path_param.at("id");
    }
    return "";
}

void handle_empty_field(const std::string& field_name, httplib::Response& res) {
    nlohmann::json response_json;
    response_json["error"] = "Field '" + field_name + "' is empty";
    res.set_content(response_json.dump(), "application/json");
    res.status = 400;
}

void send_error(httplib::Response& res, int status, const std::string& message) {
    res.status = status;
    res.set_content(R"({"message": ")" + message + R"("})", "application/json");
}