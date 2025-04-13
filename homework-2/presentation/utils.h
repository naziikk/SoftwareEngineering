#pragma once
#include "../infrastructure/third_party/httplib.h"

inline void SendError(httplib::Response& res, int status, const std::string& message) {
    res.status = status;
    nlohmann::json response_json = {
        {"message", message}
    };
    res.set_content(response_json.dump(), "application/json");
}
