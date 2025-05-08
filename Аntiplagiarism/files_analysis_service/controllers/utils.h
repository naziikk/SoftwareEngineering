#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../third_party/nlohmann/json.hpp"
#include "../third_party/httplib.h"

inline std::string extract_id_from_request(const httplib::Request& req) {
    if (!req.path_params.at("id").empty()) {
        return req.path_params.at("id");
    }
    return "";
}

inline void handle_empty_field(const std::string& field_name, httplib::Response& res) {
    nlohmann::json response_json;
    response_json["error"] = "Field '" + field_name + "' is empty";
    res.set_content(response_json.dump(), "application/json");
    res.status = 400;
}

inline void send_error(httplib::Response& res, int status, const std::string& message) {
    res.status = status;
    res.set_content(R"({"message": ")" + message + R"("})", "application/json");
}

bool is_valid_id(const httplib::Request& req) {
    if (req.path_params.at("id").empty()) {
        return false;
    }

    std::string id = req.path_params.at("id");
    for (char c : id) {
        if (!std::isalnum(c) && c != '-') {
            return false;
        }
    }

    return !id.empty();
}

void handle_empty_or_incorrect_id(const std::string& field_name, httplib::Response& res) {
    nlohmann::json response_json;
    response_json["error"] = "Field '" + field_name + "' is empty or incorrect";
    res.set_content(response_json.dump(), "application/json");
    res.status = 400;
}

bool is_digit(const char& symbol) {
    return std::isdigit(symbol);
}

bool is_vowel(const char& symbol) {
    return symbol == 'a' || symbol == 'e' || symbol == 'i' || symbol == 'o' || symbol == 'u';
}

bool is_consonant(const char& symbol) {
    return std::isalpha(symbol) && !is_vowel(symbol);
}

bool is_space(const char& symbol) {
    return std::isspace(symbol);
}

bool is_punctuation(const char& symbol) {
    return std::ispunct(symbol);
}