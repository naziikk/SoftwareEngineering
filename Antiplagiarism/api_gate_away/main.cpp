#include "controllers/analyzing_controller.h"
#include "controllers/creating_controller.h"
#include "controllers/receiver_controller.h"

#include "config/config.h"

#include "third_party/httplib.h"

#include "utils.h"

#include <unordered_map>
#include <chrono>

std::unordered_map<std::string, std::chrono::steady_clock::time_point> last_request_time;

bool is_exceed_rate_limit(const std::string& address, int milliseconds = 1000) {
    spdlog::info("Проверка на превышение лимита запросов для адреса: {}", address);
    auto now = std::chrono::steady_clock::now();
    if (last_request_time.count(address)) {
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_request_time[address]);

        if (delta.count() < milliseconds) {
            return true;
        }
    }
    last_request_time[address] = now;

    return false;
}

int main() {
    Config cfg = Config::MustLoadConfig("config/config.yaml");
    httplib::Server server;

    server.Options(".*", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Origin", req.get_header_value("Origin").c_str());
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        res.status = 200;
    });

    auto set_cors_headers = [&](httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", res.get_header_value("Origin").c_str());
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    };

    server.Post("/file/upload", [&](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        spdlog::info("[REQUEST] Получен запрос на загрузку файла");
        if (is_exceed_rate_limit(request.remote_addr)) {
            spdlog::warn("Превышен лимит запросов для адреса: {}", request.remote_addr);
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_file_type(request)) {
            spdlog::error("Некорректный тип файла, ожидается «.txt»");
            send_error(res, 400, "Invalid file type, please use «.txt»");
        } else {
            spdlog::info("Тип файла корректный, продолжаем обработку");
            add_file_to_system(request, res);
        }
    });

    server.Get("/file/:id", [&](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        spdlog::info("[REQUEST] Получен запрос на получение содержимого файла с id: {}", request.path_params.at("id"));
        if (is_exceed_rate_limit(request.remote_addr)) {
            spdlog::warn("Превышен лимит запросов для адреса: {}", request.remote_addr);
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_id(request)) {
            spdlog::error("Некорректный id в запросе, ожидается uuid + непустой");
            handle_empty_or_incorrect_id("id", res);
            send_error(res, 400, "Missing or incorrect id in path");
        } else {
            spdlog::info("Тип id корректный, продолжаем обработку");
            get_file_content_request(request, res);
        }
    });

    server.Post("/file/:id/analyze", [&](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        spdlog::info("[REQUEST] Получен запрос на анализ файла с id: {}", request.path_params.at("id"));
        if (is_exceed_rate_limit(request.remote_addr)) {
            spdlog::warn("Превышен лимит запросов для адреса: {}", request.remote_addr);
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_id(request)) {
            spdlog::error("Некорректный id в запросе, ожидается uuid + непустой");
            handle_empty_or_incorrect_id("id", res);
            send_error(res, 400, "Missing or incorrect id in path");
        } else {
            spdlog::info("Тип id корректный, продолжаем обработку");
            get_analysis(request, res);
        }
    });

    server.Get("/file/:id/words_cloud", [&](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        spdlog::info("[REQUEST] Получен запрос на получение облака слов для файла с id: {}", request.path_params.at("id"));
        if (is_exceed_rate_limit(request.remote_addr)) {
            spdlog::warn("Превышен лимит запросов для адреса: {}", request.remote_addr);
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_id(request)) {
            spdlog::error("Некорректный id в запросе, ожидается uuid + непустой");
            handle_empty_or_incorrect_id("id", res);
            send_error(res, 400, "Missing or incorrect id in path");
        } else {
            spdlog::info("Тип id корректный, продолжаем обработку");
            get_words_cloud(request, res);
        }
    });

    server.Get("/help", [&](const httplib::Request& request, httplib::Response& res) {
        set_cors_headers(res);
        if (is_exceed_rate_limit(request.remote_addr)) {
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        std::string help_text =
                "Files Storage Service API\n\n"
                "POST   /file/upload           — загрузить файл\n"
                "GET    /file/{id}             — получить содержимое файла\n"
                "GET    /file/{id}/analyze     — запустить анализ файла\n"
                "GET    /file/{id}/words_cloud — получить облако слов\n"
                "GET    /help                  — показать справку\n";

        res.set_content(help_text, "text/plain; charset=UTF-8");
    });

    server.listen(cfg.server_.host, cfg.server_.port);

    return 0;
}