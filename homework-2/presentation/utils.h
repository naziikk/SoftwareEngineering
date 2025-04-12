#pragma once
#include "../infrastructure/third_party/httplib.h"

inline void SendError(httplib::Response& res, int status, const std::string& message) {
    res.status = status;
    res.set_content(R"({"message": ")" + message + R"("})", "application/json");
}
