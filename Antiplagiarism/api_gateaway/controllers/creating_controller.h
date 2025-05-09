#pragma once

#include <iostream>
#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../utils.h"

void add_file_to_system(const httplib::Request& req, httplib::Response& res) {
    if (req.files.empty()) {
        send_error(res, 400, "No file provided");
        return;
    }

    const auto& file = req.files.begin()->second;

    httplib::Client api_gateway("http://file-storage", 8007);
    api_gateway.set_connection_timeout(10);
    api_gateway.set_read_timeout(10);

    httplib::MultipartFormDataItems items = {
            {
                    "file",
                    file.content,
                    file.filename,
                    file.content_type
            }
    };

    auto response = api_gateway.Post("/file/upload", items);

    if (response && response->status == 200) {
        nlohmann::json response_from_storage = nlohmann::json::parse(response->body);
        res.status = 200;
        res.set_content(response_from_storage.dump(), "application/json");
    } else if (response) {
        send_error(res, 400, "Error from storage: " + response->body);
    } else {
        send_error(res, 500, "Internal server error: no response from storage");
    }
}