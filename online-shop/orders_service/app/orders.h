#pragma once

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../infrastructure/database/database.h"

class Orders {
public:
    Orders(Database& database) : db_(database) {};

    Order get_orders(const std::string& user_id) {
        std::vector<std::string> params = {user_id};

        pqxx::result res = db_.execute_query("SELECT * FROM orders WHERE user_id = $1", params);
        std::vector<Order> orders;
        for (const auto& row : res) {
            Order order;
            order.id = row["id"].as<std::string>();
            order.description = row["description"].as<std::string>();
            order.amount = row["amount"].as<long long>();

            orders.push_back(order);
        }

        return orders;
    }

    Order get_order(const std::string& user_id, const std::string& order_id) {
        std::vector<std::string> params = {user_id, order_id};

        pqxx::result res = db_.execute_query("SELECT * FROM orders WHERE user_id = $1 AND id = $2", params);

        if (res.empty()) {
            return {};
        }

        Order order;
        order.id = res[0]["id"].as<std::string>();
        order.description = res[0]["description"].as<std::string>();
        order.amount = res[0]["amount"].as<long long>();

        return order;
    }

private:
    struct Order {
        std::string id;
        std::string description;
        long long amount;
    };

    using json = nlohmann::json();
    Database& db_;
};

