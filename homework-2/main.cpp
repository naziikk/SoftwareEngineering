#include "infrastructure/third_party/httplib.h"
#include "infrastructure/config/config.h"
#include "presentation/AnimalController.h"
#include "presentation//EnclosureController.h"
#include "presentation/ZooStatisticsController.h"
#include "presentation/FeedingScheduleController.h"
#include "app/FeedingOrganizationService.h"

int main() {
    // TODO: разобраться с багом с last_fed_time
    Config config = Config::MustLoadConfig("/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-2/infrastructure/config/config.yaml");

    AnimalRepository animal_repository;
    EnclosureRepository enclosure_repository(animal_repository);
    AnimalService animal_service(animal_repository, enclosure_repository);
    FeedingOrganizationService feeding_service(animal_repository);
    ZooStatisticsService zoo_service(animal_repository, enclosure_repository, feeding_service);

    httplib::Server server;

    std::thread feeding_thread([&feeding_service]() { // сделаем планировщик для постоянного подкармливания животных
        while (true) {
            feeding_service.FeedAnimals();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    });

    server.Post("/animal", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.AddAnimal(request, res);
    });

    server.Delete("/animal/:id", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.RemoveAnimal(request, res);
    });

    server.Post("/animal/:id/feed", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.FeedAnimal(request, res);
    });

    server.Post("/animal/:id/health_check", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
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

    server.Post("/enclosure/:id/clean", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        EnclosureController controller(animal_service, animal_repository);
        controller.CleanAnEnclosureRequest(request, res);
    });

    server.Put("/animal/:id/move", [&animal_service, &enclosure_repository, &animal_repository](const httplib::Request& request, httplib::Response &res) {
        AnimalController controller(animal_service, enclosure_repository);
        controller.MoveAnimal(request, res);
    });

    server.Post("/animal/:id/feeding_schedule/1", [&animal_service, &animal_repository, &feeding_service](const httplib::Request& request, httplib::Response &res) {
        FeedingScheduleController controller(animal_service, animal_repository, feeding_service);
        controller.AddScheduleRequest(request, res);
    });

    server.Put("/animal/:id/feeding_schedule/2", [&animal_service, &animal_repository, &feeding_service](const httplib::Request& request, httplib::Response &res) {
        FeedingScheduleController controller(animal_service, animal_repository, feeding_service);
        controller.UpdateScheduleRequest(request, res);
    });

    server.Delete("/animal/:id/feeding_schedule/3", [&animal_service, &animal_repository, &feeding_service](const httplib::Request& request, httplib::Response &res) {
        FeedingScheduleController controller(animal_service, animal_repository, feeding_service);
        controller.CancelScheduleRequest(request, res);
    });

    server.Get("/zoo/statistics", [&zoo_service](const httplib::Request& request, httplib::Response &res) {
        ZooStatisticsController controller(zoo_service);
        controller.GetAllStatisticsRequest(request, res);
    });

    server.listen(config.server_.host, config.server_.port);
    feeding_thread.detach();
}