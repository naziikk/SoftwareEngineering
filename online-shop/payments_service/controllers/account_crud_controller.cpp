#include "account_crud_controller.h"

void AccountCrudController::get_account_balance_request(const httplib::Request& request, httplib::Response& res) {
    if (!is_valid_id(request)) {
        send_error(res, 400, "Плохой id");
        return;
    }

    std::string user_id = request.path_params.at("id");

    long long balance = balance_provider_.get_balance(user_id);

    if (balance == LLONG_MIN) {
        send_error(res, 404, "Account not found");
        return;
    }

    json response_json;
    response_json["user_id"] = user_id;
    response_json["balance"] = balance;

    res.set_content(response_json.dump(), "application/json");
}

void AccountCrudController::create_account_request(const httplib::Request& request, httplib::Response& res) {
    auto parsed = json::parse(request.body);
    if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
        handle_empty_or_incorrect_id("user_id", res);
        return;
    }

    std::string user_id = parsed["user_id"].get<std::string>();

    if (!account_creator_.create_account(user_id)) {
        send_error(res, 400, "Account already exists or creation failed");
        return;
    }

    res.status = 201;
    res.set_content(R"({"message": "Аккаунт успешно создан!"})", "application/json");
}

void AccountCrudController::account_top_up_request(const httplib::Request &request, httplib::Response &res) {
    auto parsed = json::parse(request.body);
    if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
        handle_empty_or_incorrect_id("user_id", res);
        return;
    }

    std::string user_id = parsed["user_id"].get<std::string>();
    std::string amount = parsed["amount"].get<std::string>();

    if (!balance_provider_.top_up_balance(user_id, amount)) {
        send_error(res, 404, "Account not found or top-up failed");
        return;
    }

    res.status = 200;
    res.set_content(R"({"message": "Баланс успешно пополнен!"})", "application/json");
}