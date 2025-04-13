#include "infrastructure/third_party/httplib.h"
#include "infrastructure/config/config.h"
#include "presentation/AnimalController.h"
#include "presentation//EnclosureController.h"
#include "presentation/ZooStatisticsController.h"

int main() {
    Config config = Config::MustLoadConfig("/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-2/infrastructure/config/config.yaml");
    AnimalRepository animal_repository;
    EnclosureRepository enclosure_repository(animal_repository);
    AnimalService animal_service(animal_repository, enclosure_repository);
    httplib::Server server;

    server.Post("/animal", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.AddAnimal(request, res);
    });

    server.Delete("/animal/:id", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.RemoveAnimal(request, res);
    });

    server.Patch("/animal/:id/feed", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.FeedAnimal(request, res);
    });

    server.Patch("/animal/:id/health_check", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.HealAnimal(request, res);
    });

    server.Post("/enclosure", [&animal_repository, &animal_service](const httplib::Request& request, httplib::Response &res) {
        EnclosureController controller(animal_service, animal_repository);
        controller.AddEnclosure(request, res);
    });

    server.Delete("/enclosure/:id", [&animal_repository, &animal_service](const httplib::Request& request, httplib::Response &res) {
        EnclosureController controller(animal_service, animal_repository);
        controller.RemoveEnclosure(request, res);
    });

    server.Put("/animal/:id/move", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.MoveAnimal(request, res);
    });

    server.Get("/feeding_schedule", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Post("/feeding_schedule", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.Get("/zoo/statistics", [](const httplib::Request& request, httplib::Response &res) {

    });

    server.listen(config.server_.host, config.server_.port);
}