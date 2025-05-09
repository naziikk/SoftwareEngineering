#pragma once

#include <iostream>
#include "../utils.h"
#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

#include "receiver_controller.h"

void get_analysis(const httplib::Request& req, httplib::Response& res) {
    get_file_content_request(req, res);

    if (res.status != 200) {
        send_error(res, 400, "Error from storage");
        return;
    }

    std::string document_id = nlohmann::json::parse(res.body)["id"];

    httplib::Client api_gate_away("http://file-analyse:8008");
    api_gate_away.set_connection_timeout(10);
    api_gate_away.set_read_timeout(10);
    api_gate_away.set_default_headers({
            {"Content-Type", "application/json"},
            {"Accept", "application/json"}
    });

    auto response = api_gate_away.Post("/file/" + document_id + "/analysis", "{}", "application/json");

    if (response && response->status == 200) {
        nlohmann::json response_from_storage = nlohmann::json::parse(response->body);
        res.status = 200;
        res.set_content(response_from_storage.dump(), "application/json");
    }

    if (response) {
        send_error(res, 400, "Error from storage");
    } else {
        send_error(res, 500, "Internal server error");
    }
}

void get_words_cloud(const httplib::Request& req, httplib::Response& res) {
    std::string document_id = extract_id_from_request(req);

    httplib::Client api_gate_away("http://file-analyse:8008");
    api_gate_away.set_connection_timeout(10);
    api_gate_away.set_read_timeout(10);
    api_gate_away.set_default_headers({
            {"Content-Type", "application/json"},
            {"Accept", "application/json"}
    });

    auto response = api_gate_away.Get("/words_cloud/" + document_id);

    if (response && response->status == 200) {
        nlohmann::json response_from_storage = nlohmann::json::parse(response->body);
        res.status = 200;
        res.set_content(response_from_storage.dump(), "application/json");
    }

    if (response) {
        send_error(res, 400, "Error from analysis service");
    } else {
        send_error(res, 500, "Internal server error");
    }
}