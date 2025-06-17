#include "../utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

class OrdersOperationsController {
public:
    void get_orders_request(const httplib::Request& req, httplib::Response& res) {
        auto start_time = std::chrono::steady_clock::now();
        std::string request_id = uuid::generate_uuid();

        std::string user_id = extract_id_from_request(req);

        spdlog::info("[{}] Запрос на получение списка заказов от пользователя user_id: {}", request_id, user_id);

        httplib::Client api("http://orders:8008");
        api.set_connection_timeout(10);
        api.set_read_timeout(10);
        api.set_default_headers({
                {"Content-Type", "application/json"},
                {"Accept", "application/json"}
        });

        std::string path = "/orders/" + user_id + "/list";

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
            spdlog::warn("[{}] Ошибка от сервиса заказов: status {}, body: {}", request_id, response->status, response->body);
            send_error(res, 400, "Error from analysis service");
        } else {
            spdlog::error("[{}] Не удалось подключиться к сервису заказов", request_id);
            send_error(res, 500, "Internal server error");
        }

        auto end_time = std::chrono::steady_clock::now();
        spdlog::debug("[{}] Получение истории заказов завершено за {} мс", request_id,
                      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }

    void get_order_info_request(const httplib::Request& req, httplib::Response& res) {
        auto start_time = std::chrono::steady_clock::now();
        std::string request_id = uuid::generate_uuid();

        std::string order_id = req.path_params.at("id");
        std::string user_id = json::parse(req.body).at("user_id");

        spdlog::info("[{}] Запрос на получение заказа: {} от пользователя user_id: {}", order_id, request_id, user_id);

        httplib::Client api("http://orders:8008");
        api.set_connection_timeout(10);
        api.set_read_timeout(10);
        api.set_default_headers({
                {"Content-Type", "application/json"},
                {"Accept", "application/json"}
        });

        std::string path = "/orders/" + order_id;

        json body = {
                {"user_id", user_id}
        };

        auto response = api.Post(path, body.dump(), "application/json");

        if (response && response->status == 200) {
            try {
                nlohmann::json json_response = nlohmann::json::parse(response->body);
                res.status = 200;
                res.set_content(json_response.dump(), "application/json");
            } catch (const std::exception& e) {
                send_error(res, 500, "Invalid response");
            }
        } else if (response) {
            spdlog::warn("[{}] Ошибка от сервиса заказов: status {}, body: {}", request_id, response->status, response->body);
            send_error(res, 400, "Error from analysis service");
        } else {
            spdlog::error("[{}] Не удалось подключиться к сервису заказов", request_id);
            send_error(res, 500, "Internal server error");
        }

        auto end_time = std::chrono::steady_clock::now();
        spdlog::debug("[{}] Получение истории заказов завершено за {} мс", request_id,
                      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }

    void create_order_request(const httplib::Request& req, httplib::Response& res) {
        auto start_time = std::chrono::steady_clock::now();
        std::string request_id = uuid::generate_uuid();

        auto parsed = json::parse(req.body);
        spdlog::info("[{}] Распарсили данные при создании заказа", request_id);
        std::string user_id = parsed["user_id"];
        std::string amount = parsed["amount"].get<std::string>();
        std::string description = parsed["description"];
        spdlog::info("[{}] Получили данные при создании заказа", request_id);

        spdlog::info("[{}] Запрос на создание заказа от пользователя user_id: {}", request_id, user_id);

        httplib::Client api("http://orders:8008");
        api.set_connection_timeout(10);
        api.set_read_timeout(10);
        api.set_default_headers({
                {"Content-Type", "application/json"},
                {"Accept", "application/json"}
        });

        std::string path = "/order/create";

        json body = {
                {"user_id", user_id},
                {"amount", amount},
                {"description", description}};

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
            spdlog::warn("[{}] Ошибка от сервиса заказов: status {}, body: {}", request_id, response->status, response->body);
            send_error(res, 400, "Error from analysis service");
        } else {
            spdlog::error("[{}] Не удалось подключиться к сервису заказов", request_id);
            send_error(res, 500, "Internal server error");
        }

        auto end_time = std::chrono::steady_clock::now();
        spdlog::debug("[{}] Создание заказа завершено за {} мс", request_id,
                      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }

private:
    using json = nlohmann::json;
};