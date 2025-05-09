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
    Config cfg = Config::MustLoadConfig("../config/config.yaml");
    httplib::Server server;

    server.Post("/file/upload", [&](const httplib::Request& request, httplib::Response &res) {
        if (is_exceed_rate_limit(request.remote_addr)) {
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_file_type(request)) {
            send_error(res, 400, "Invalid file type, please use «.txt»");
        } else {
            add_file_to_system(request, res);
        }
    });

    server.Get("/file/:id", [&](const httplib::Request& request, httplib::Response &res) {
        if (is_exceed_rate_limit(request.remote_addr)) {
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_id(request)) {
            handle_empty_or_incorrect_id("id", res);
            send_error(res, 400, "Missing or incorrect id in path");
        } else {
            get_file_content_request(request, res);
        }
    });

    server.Get("/file/:id/analyze", [&](const httplib::Request& request, httplib::Response &res) {
        if (is_exceed_rate_limit(request.remote_addr)) {
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_id(request)) {
            handle_empty_or_incorrect_id("id", res);
            send_error(res, 400, "Missing or incorrect id in path");
        } else {
            get_analysis(request, res);
        }
    });

    server.Get("/file/:id/words_cloud", [&](const httplib::Request& request, httplib::Response &res) {
        if (is_exceed_rate_limit(request.remote_addr)) {
            send_error(res, 429, "Rate limit exceeded");
            return;
        }

        if (!is_valid_id(request)) {
            handle_empty_or_incorrect_id("id", res);
            send_error(res, 400, "Missing or incorrect id in path");
        } else {
            get_words_cloud(request, res);
        }
    });

    server.Get("/help", [&](const httplib::Request& request, httplib::Response& res) {
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