#include "account_crud_controller.h"

void AccountCrudController::get_account_balance_request(const httplib::Request& request, httplib::Response& res) {
    std::cout << "=== START get_account_balance_request ===\n";
    std::cout << "Проверяем валидность ID...\n";

    if (!is_valid_id(request)) {
        std::cout << "Ошибка: ID невалиден\n";
        send_error(res, 400, "Плохой id");
        return;
    }

    std::string user_id = request.path_params.at("id");
    std::cout << "Получен user_id: " << user_id << "\n";

    std::cout << "Запрашиваем баланс для user_id: " << user_id << "\n";
    long long balance = balance_provider_.get_balance(user_id);
    std::cout << "Получен баланс: " << balance << "\n";

    if (balance == LLONG_MIN) {
        std::cout << "Ошибка: Аккаунт не найден\n";
        send_error(res, 404, "Аккаунт не найден");
        return;
    }

    json response_json;
    response_json["user_id"] = user_id;
    response_json["balance"] = std::to_string(balance);

    res.status = 200;
    res.set_content(response_json.dump(), "application/json");
    std::cout << "=== END get_account_balance_request ===\n";
}

void AccountCrudController::create_account_request(const httplib::Request& request, httplib::Response& res) {
    std::cout << "=== START create_account_request ===\n";
    std::cout << "Получено тело запроса: " << request.body << "\n";

    try {
        auto parsed = json::parse(request.body);
        std::cout << "JSON успешно распарсен\n";

        if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
            std::cout << "Ошибка: user_id отсутствует или не строка\n";
            handle_empty_or_incorrect_id("user_id", res);
            return;
        }

        std::string user_id = parsed["user_id"];
        std::cout << "ЗДРАВСТВУЙТЕ, МЫ УЖЕ ТУТ! user_id: " << user_id << "\n";

        std::cout << "Пытаемся создать аккаунт для user_id: " << user_id << "\n";
        if (!account_creator_.create_account(user_id)) {
            std::cout << "Ошибка: Аккаунт уже существует\n";
            send_error(res, 400, "Аккаунта уже существует");
            return;
        }

        std::cout << "Аккаунт успешно создан\n";
        res.status = 201;
        res.set_content(R"({"message": "Аккаунт успешно создан!"})", "application/json");
    } catch (const std::exception& e) {
        std::cout << "Ошибка при обработке запроса: " << e.what() << "\n";
        send_error(res, 400, "Неверный формат запроса");
    }
    std::cout << "=== END create_account_request ===\n";
}

void AccountCrudController::account_top_up_request(const httplib::Request &request, httplib::Response &res) {
    std::cout << "=== START account_top_up_request ===\n";
    std::cout << "Получено тело запроса: " << request.body << "\n";

    try {
        auto parsed = json::parse(request.body);
        std::cout << "JSON успешно распарсен\n";

        if (!parsed.contains("user_id") || !parsed["user_id"].is_string()) {
            std::cout << "Ошибка: user_id отсутствует или не строка\n";
            handle_empty_or_incorrect_id("user_id", res);
            return;
        }

        if (!parsed.contains("amount")) {
            std::cout << "Ошибка: amount отсутствует\n";
            send_error(res, 400, "Не указана сумма");
            return;
        }

        std::string user_id = parsed["user_id"].get<std::string>();
        std::string amount = parsed["amount"].get<std::string>();
        std::cout << "Пополнение баланса для user_id: " << user_id << ", сумма: " << amount << "\n";

        if (!balance_provider_.top_up_balance(user_id, amount)) {
            std::cout << "Ошибка: Аккаунт не существует или ошибка при пополнении\n";
            send_error(res, 404, "Аккаунта не существует или ошибка при пополнении");
            return;
        }

        std::cout << "Баланс успешно пополнен\n";
        res.status = 200;
        res.set_content(R"({"message": "Баланс успешно пополнен!"})", "application/json");
    } catch (const std::exception& e) {
        std::cout << "Ошибка при обработке запроса: " << e.what() << "\n";
        send_error(res, 400, "Неверный формат запроса");
    }
    std::cout << "=== END account_top_up_request ===\n";
}