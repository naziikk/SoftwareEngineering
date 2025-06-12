#include "get_orders_controller.h"

void GetOrdersController::get_orders_request(const httplib::Request& req, httplib::Response& res) {
    auto parsed = json::parse(req.body);
    if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
        handle_empty_or_incorrect_id("user_id", res);
        return;
    }

    std::string user_id = parsed["user_id"].get<std::string>();

    Order orders = orders_service_.get_orders(user_id);
    if (orders.empty()) {
        send_error(res, 404, "Не найдено активных заказов для пользователя");
        return;
    }
    json response_json;
    for (const auto& order : orders) {
        json order_json;
        order_json["id"] = order.id;
        order_json["description"] = order.description;
        order_json["amount"] = order.amount;
        response_json.push_back(order_json);
    }

    res.set_content(response_json.dump(), "application/json");
    res.status = 200;
}

void GetOrdersController::get_order_by_id_request(const httplib::Request& req, httplib::Response& res) {
    if (!is_valid_id(req)) {
        handle_empty_or_incorrect_id("order_id", res);
        return;
    }

    std::string order_id = extract_id_from_request(req);
    if (order_id.empty()) {
        handle_empty_or_incorrect_id("order_id", res);
        return;
    }

    auto parsed = json::parse(req.body);
    if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
        handle_empty_or_incorrect_id("user_id", res);
        return;
    }

    std::string user_id = parsed["user_id"].get<std::string>();
    Order order = orders_service_.get_order(user_id, order_id);
    if (order.id.empty()) {
        send_error(res, 404, "Заказ не найден для такого user_id и order_id");
        return;
    }

    json response_json;

    response_json["id"] = order.id;
    response_json["description"] = order.description;
    response_json["amount"] = order.amount;

    res.set_content(response_json.dump(), "application/json");
    res.status = 200;
}