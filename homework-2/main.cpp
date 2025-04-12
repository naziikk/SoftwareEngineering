#include "infrastructure/third_party/httplib.h"
#include "infrastructure/config/config.h"
#include "presentation/AnimalController.h"
#include "presentation//EnclosureController.h"
#include "presentation/ZooStatisticsController.h"

int main() {
    Config config = Config::MustLoadConfig("config.yaml");

    httplib::Server server;

    server.Post("/animal", [](const httplib::Request& request, httplib::Response &res) {
        AnimalController::AddAnimal(request, res);
    });

    server.Delete("/animal/:id", [](const httplib::Request& request, httplib::Response &res) {
        AnimalController::RemoveAnimal(request, res);
    });

    server.Post("/enclosure", [](const httplib::Request& request, httplib::Response &res) {
        EnclosureController::AddEnclosure(request, res);
    });

    server.Delete("/enclosure/:id", [](const httplib::Request& request, httplib::Response &res) {
        EnclosureController::RemoveEnclosure(request, res);
    });

    server.Put("/animal/:id/move", [](const httplib::Request& request, httplib::Response &res) {
        AnimalController::MoveAnimal(request, res);
    });

    server.Get("/feeding_schedule", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Post("/feeding_schedule", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Get("/zoo/statistics", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.listen(config.server_.host, config.server_.port);
}