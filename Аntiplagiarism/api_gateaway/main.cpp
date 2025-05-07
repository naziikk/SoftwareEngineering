#include "controllers/analyzing_controller.h"
#include "controllers/creating_controller.h"
#include "controllers/receiver_controller.h"
#include "config/config.h"
#include "third_party/httplib.h"
#include "utils.h"

int main() {
    Config cfg = Config::MustLoadConfig("/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/Аntiplagiarism/api_gateaway/config/config.yaml");
    httplib::Server server;

    try {
        server.Post("/file/upload", [](const httplib::Request& request, httplib::Response &res) {
            if (!is_valid_file_type(request)) {
                send_error(res, 400, "Invalid file type, please use «.txt»");
            } else {
                add_file_to_system(request, res);
            }
        });

        server.Get("/file/:id", [](const httplib::Request& request, httplib::Response &res) {
            if (!is_valid_id(request)) {
                handle_empty_or_incorrect_id("id", res);
                send_error(res, 400, "Missing or incorrect id in path");
            } else {

            }
        });

        server.Get("/file/:id/analyze", [](const httplib::Request& request, httplib::Response &res) {
            if (!is_valid_id(request)) {
                handle_empty_or_incorrect_id("id", res);
                send_error(res, 400, "Missing or incorrect id in path");
            } else {
                get_analysis(request, res);
            }
        });

        server.Get("/file/:id/words_cloud", [](const httplib::Request& request, httplib::Response &res) {
            if (!is_valid_id(request)) {
                handle_empty_or_incorrect_id("id", res);
                send_error(res, 400, "Missing or incorrect id in path");
            } else {
                get_words_cloud(request, res);
            }
        });

        server.Get("/help", [](const httplib::Request&, httplib::Response& res) {
            std::string help_text =
                    "Files Storage Service API\n\n"
                    "POST   /file/upload           — загрузить файл\n"
                    "GET    /file/{id}             — получить содержимое файла\n"
                    "GET    /file/{id}/analyze     — запустить анализ файла\n"
                    "GET    /file/{id}/words_cloud — получить облако слов\n"
                    "GET    /help                  — показать справку\n";

            res.set_content(help_text, "text/plain; charset=UTF-8");
        });

    } catch (...) {
        std::cerr << "Some shit happens" << '\n';
        return 1;
    }

    server.listen(cfg.server_.host, cfg.server_.port);

    return 0;
}