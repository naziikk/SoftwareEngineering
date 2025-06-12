#include "account_crud_controller.h"

void AccountCrudController::get_account_balance_request(const httplib::Response& res, httplib::Response& res) {
    auto parsed = json::parse(req.body);
    if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
        handle_empty_or_incorrect_id("user_id", res);
        return;
    }

    std::string user_id = parsed["user_id"].get<std::string>();
}

void AccountCrudController::create_account_request(const httplib::Response& res, httplib::Response& res) {
    auto parsed = json::parse(req.body);
    if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
        handle_empty_or_incorrect_id("user_id", res);
        return;
    }

    std::string user_id = parsed["user_id"].get<std::string>();
}