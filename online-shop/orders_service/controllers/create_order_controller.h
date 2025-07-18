#pragma once
#include "../utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../infrastructure/kafka/kafka_producer.h"
#include "../infrastructure/database/database.h"

class OrderCreatingController {
public:
    OrderCreatingController(Database& db) : db_(db) {};

    void create_order_request(const httplib::Request& req, httplib::Response& res) {
        auto parsed = json::parse(req.body);

        std::string user_id = parsed["user_id"];
        std::string amount = parsed["amount"];
        std::string description = parsed["description"];

        std::cout << user_id << ' ' << amount << ' ' << description << '\n';

        std::string query = "INSERT INTO orders_storage.outbox (user_id, description, amount) VALUES ($1, $2, $3)";
        std::vector<std::string> params = {user_id, description, amount};

        try {
            db_.execute_query(query, params);
        } catch (...) {
            std::cout << "Ошибка при выполнении запроса к базе данных" << '\n';
        }

        json order_details;
        order_details["message"] = "Order successfully created!";
        order_details["user_id"] = user_id;
        order_details["description"] = description;
        order_details["amount"] = amount;

        res.status = 201;
        res.set_content(order_details.dump(), "application/json");
    }

private:
    using json = nlohmann::json;
    Database& db_;
};