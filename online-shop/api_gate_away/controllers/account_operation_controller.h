#include "../utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

class AccountOperationsController {
public:
    void create_account_request(const httplib::Request& req, httplib::Response& res) {
        auto start_time = std::chrono::steady_clock::now();
        std::string request_id = uuid::generate_uuid();

        std::string user_id = json::parse(req.body).at("user_id");

        spdlog::info("[{}] Запрос на создание аккаунта от пользователя user_id: {}", request_id, user_id);

        httplib::Client api("http://payments:8007");
        api.set_connection_timeout(10);
        api.set_read_timeout(10);
        api.set_default_headers({
                {"Content-Type", "application/json"},
                {"Accept", "application/json"}
        });

        std::string path = "/account";

        json body = {{"user_id", user_id}};

        auto response = api.Post(path, body.dump(), "application/json");

        if (response && (response->status == 200 || response->status == 201)) {
            try {
                nlohmann::json json_response = nlohmann::json::parse(response->body);
                res.status = response->status;
                res.set_content(json_response.dump(), "application/json");
            } catch (const std::exception& e) {
                send_error(res, 500, "Invalid response");
            }
        } else if (response) {
            spdlog::warn("[{}] Ошибка от сервиса платежей: status {}, body: {}", request_id, response->status, response->body);
            send_error(res, 400, "Error from analysis service");
        } else {
            spdlog::error("[{}] Не удалось подключиться к сервису платежей", request_id);
            send_error(res, 500, "Internal server error");
        }

        auto end_time = std::chrono::steady_clock::now();
        spdlog::debug("[{}] Создание аккаунта завершено за {} мс", request_id,
                      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }

    void get_account_balance_request(const httplib::Request& req, httplib::Response& res) {
        auto start_time = std::chrono::steady_clock::now();
        std::string request_id = uuid::generate_uuid();

        std::string user_id = req.path_params.at("id");

        spdlog::info("[{}] Запрос на получение баланса аккаунта от пользователя user_id: {}", request_id, user_id);

        httplib::Client api("http://payments:8007");
        api.set_connection_timeout(10);
        api.set_read_timeout(10);
        api.set_default_headers({
                {"Content-Type", "application/json"},
                {"Accept", "application/json"}
        });

        std::string path = "/account/" + user_id + "/balance";

        auto response = api.Get(path);

        if (response && response->status == 200) {
            try {
                nlohmann::json json_response = nlohmann::json::parse(response->body);
                res.status = 200;
                res.set_content(json_response.dump(), "application/json");
            } catch (const std::exception& e) {
                send_error(res, 500, "Invalid response");
            }
        } else if (response) {
            spdlog::warn("[{}] Ошибка от сервиса платежей: status {}, body: {}", request_id, response->status, response->body);
            send_error(res, 400, "Error from analysis service");
        } else {
            spdlog::error("[{}] Не удалось подключиться к сервису платежей", request_id);
            send_error(res, 500, "Internal server error");
        }

        auto end_time = std::chrono::steady_clock::now();
        spdlog::debug("[{}] Получение баланса аккаунта завершено за {} мс", request_id,
                      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }

    void account_top_up_request(const httplib::Request& req, httplib::Response& res) {
        auto start_time = std::chrono::steady_clock::now();
        std::string request_id = uuid::generate_uuid();

        std::string user_id = json::parse(req.body).at("user_id");
        std::string amount = json::parse(req.body).at("amount");

        spdlog::info("[{}] Запрос на пополнение баланса аккаунта от пользователя user_id: {}", request_id, user_id);

        httplib::Client api("http://payments:8007");
        api.set_connection_timeout(10);
        api.set_read_timeout(10);
        api.set_default_headers({
                {"Content-Type", "application/json"},
                {"Accept", "application/json"}
        });

        std::string path = "/account/top_up";

        nlohmann::json request_body = {
                {"user_id", user_id},
                {"amount", amount}
        };

        auto response = api.Post(path, request_body.dump(), "application/json");

        if (response && response->status == 200) {
            try {
                nlohmann::json json_response = nlohmann::json::parse(response->body);
                res.status = 200;
                res.set_content(json_response.dump(), "application/json");
            } catch (const std::exception& e) {
                send_error(res, 500, "Invalid response");
            }
        } else if (response) {
            spdlog::warn("[{}] Ошибка от сервиса платежей: status {}, body: {}", request_id, response->status, response->body);
            send_error(res, 400, "Error from analysis service");
        } else {
            spdlog::error("[{}] Не удалось подключиться к сервису платежей", request_id);
            send_error(res, 500, "Internal server error");
        }

        auto end_time = std::chrono::steady_clock::now();
        spdlog::debug("[{}] Получение баланса аккаунта завершено за {} мс", request_id,
                      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }

private:
    using json = nlohmann::json;
};