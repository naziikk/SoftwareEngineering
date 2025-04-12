#include "infrastructure/third_party/httplib.h"
#include "infrastructure/config/config.h"

int main() {
    Config config = Config::MustLoadConfig("config.yaml");

    httplib::Server server;

    server.Post("/animal", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Delete("/animal/:id", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Post("/enclosure", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Delete("/enclosure/:id", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Put("/animal/:id/move", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Get("/feeding_schedule", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Post("/feeding_schedule", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Get("/zoo/statistics", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.listen(config.server_.host, config.server_.port);
}