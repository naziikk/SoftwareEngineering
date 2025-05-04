#include <iostream>
#include <vector>
#include <string>
#include "third_party/nlohmann/nlohmann.hpp"
#include "third_party/httplib.h"

bool is_valid_id(const httplib::Request& req) {
    if (req.path_param.at("id").empty()) {
        return false;
    }

    std::string id = req.path_param.at("id");
    for (char c : id) {
        if (!std::isalnum(c) && c != '-') {
            return false;
        }
    }

    return !id.empty();
}

bool is_valid_file_type(const httplib::Request& req) {
    const std::vector<std::string> valid_file_types = {"txt", "pdf", "docx", "xlsx"};
    auto parsed = json::parse(req.body);

    std::string file_name = parsed["file_name"];

    if (!req.has_file(file_name)) {
        send_error(res, 401, "Missing file content");
        return;
    }

    httplib::MultipartFormData file = req.get_file_value(file_name);
    std::string file_extension = file.filename.substr(file.filename.find_last_of('.') + 1);

    return valid_file_types.contains(file_extension);
}

void handle_empty_or_incorrect_id(const std::string& field_name, httplib::Response& res) {
    nlohmann::json response_json;
    response_json["error"] = "Field '" + field_name + "' is empty or incorrect";
    res.set_content(response_json.dump(), "application/json");
    res.status = 400;
}

void send_error(httplib::Response& res, int status, const std::string& message) {
    res.status = status;
    res.set_content(R"({"message": ")" + message + R"("})", "application/json");
}