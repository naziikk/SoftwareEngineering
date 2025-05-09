#include <iostream>
#include "database/decorator/Facade.h"
#include "src/executor/Invoker.h"
#include <spdlog/spdlog.h>
#include "src/observer/Observer.h"
#include "src/factory/CommandFactory.h"
#include "src/helper.h"
#include "src/importer/ReadData.h"

int main() {
    DIContainer container;
    container.RegisterObject<DatabaseFacade>("dbname=finance_tracker host=localhost port=5432");
    container.RegisterObject<Invoker>();
    container.RegisterObject<Logger>();

    auto db = container.GetObject<DatabaseFacade>();
    db->Init("../infrastructure/migrations/init_db.sql");

    auto invoker = container.GetObject<Invoker>();
    auto logger = container.GetObject<Logger>();
    auto commandFactory = container.GetObject<CommandFactory>();

    invoker->AddObserver(logger);

    std::cout << "Добро пожаловать в наш банк!\n";

    while (true) {
        ShowMenu();
        int choice;
        std::cin >> choice;

        if (choice == 10) {
            std::cout << "Спасибо, что посетили наш банк!\n";
            break;
        } else if (choice == 9) {
            std::cout << "Введите название файла с данными: ";
            std::string filename;
            std::cin >> filename;
            bool result = FillDatabase("../" + filename, *db);

            if (result) {
                std::cout << "Данные успешно загружены в базу данных!\n";
            } else {
                std::cout << "Ошибка при загрузке данных в базу данных! Возможно данные не соответствуют формату :(\n";
            }
        }

        auto command = CommandFactory::CreateCommand(choice, *db);
        if (command) {
            invoker->SetCommand(command);
            invoker->RunCommand();
        } else {
            std::cout << "Введите корректное число!\n";
        }
    }
}
