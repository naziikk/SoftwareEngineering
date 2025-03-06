#include <iostream>
#include "src/executor/Invoker.h"
#include <spdlog/spdlog.h>
#include "src/observer/Observer.h"
#include "src/factory/CommandFactory.h"
#include "src/helper.h"

//### User Stories
//- добавление нового счета (запрашиваем название счета) -> создаем счет с нулевым балансом в DB
//- добавление новой категории (запрашиваем тип категории: доход/расход) -> добавляем новую категорию в DB
//- получение всех счетов -> отдаем счета в формате (название счета: id счета)
//- пополнение конкретного счета по id -> пользователь вводит сумму -> обновляем данные в DB
//- произведение операции (указываем категорию платежа: доход/расход, сумму, название счета, название категории платежа)
//-> проверяем достаточно ли средств на балансе -> если нет - выдаем ошибку -> иначе фиксируем операцию и добавляем в лог
//- получение выгрузки операции в файл -> запрашиваем название выходного файла + формат (JSON/YAML/CSV)

int main() {
    Invoker invoker;

    DatabaseFacade db("dbname=finance_tracker host=localhost port=5432");
    db.Init("../database/migrations/init_db.sql");
    pqxx::connection connection_("dbname=finance_tracker host=localhost port=5432");
    pqxx::work worker(connection_);

    auto logger = std::make_shared<Logger>();
    invoker.AddObserver(logger);
    std::cout << "Добро пожаловать в наш банк!\n";

    while (true) {
        ShowMenu();
        int choice;
        std::cin >> choice;

        if (choice == 9) {
            std::cout << "Спасибо, что посетили наш банк!\n";
            break;
        }

        auto command = CommandFactory::CreateCommand(choice, db);
        if (command) {
            invoker.SetCommand(command);
            invoker.RunCommand();
        } else {
            std::cout << "Введите корректное число!\n";
        }
    }
}
