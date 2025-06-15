#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <sstream>

#include "third_party/nlohmann/json.hpp"
#include "third_party/httplib.h"

#include "infrastructure/kafka/kafka_producer.h"
#include "infrastructure/database/database.h"

inline bool is_valid_id(const httplib::Request& req) {
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

inline void handle_empty_or_incorrect_id(const std::string& field_name, httplib::Response& res) {
    nlohmann::json response_json;
    response_json["error"] = "Field '" + field_name + "' is empty or incorrect";
    res.set_content(response_json.dump(), "application/json");
    res.status = 400;
}

inline void send_error(httplib::Response& res, int status, const std::string& message) {
    res.status = status;
    res.set_content(R"({"message": ")" + message + R"("})", "application/json");
}

inline std::string extract_id_from_request(const httplib::Request& req) {
    if (!req.path_params.at("id").empty()) {
        return req.path_params.at("id");
    }
    return "";
}

inline void start_outbox(Database& db, KafkaProducer& producer) {
    std::thread([&db, &producer]() {
        while (true) {
            try {
                std::string select_query = "SELECT id, user_id, description, amount FROM orders_storage.outbox WHERE status = 'NOT_SENT'";
                std::vector<std::string> params;
                auto results = db.execute_query(select_query, params);

                for (const auto& row : results) {
                    std::string id = row["id"].as<std::string>();
                    std::string user_id = row["user_id"].as<std::string>();
                    std::string description = row["description"].as<std::string>();
                    std::string amount = row["amount"].as<std::string>();

                    nlohmann::json message = {
                            {"user_id", user_id},
                            {"description", description},
                            {"amount", amount}
                    };

                    producer.send(message.dump());

                    std::string update_query =
                            "UPDATE orders_storage.outbox SET status = 'SENT' WHERE id = $1";
                    std::vector<std::string> update_params = {id};
                    db.execute_query(update_query, update_params);
                }

            } catch (const std::exception& e) {
                std::cerr << "Ошибка в Outbox обработчике: " << e.what() << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }).detach();
}

namespace uuid {
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    inline std::string generate_uuid() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }
}