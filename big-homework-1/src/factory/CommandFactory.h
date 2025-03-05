#include <iostream>
#include "../executor/ProcessRequest.h"

class CommandFactory {
public:
    static std::shared_ptr<Command> CreateCommand(int choice, DatabaseFacade& db) {
        switch (choice) {
            case 1: {
                std::string account_name;
                std::cout << "Введите название счета: ";
                std::cin >> account_name;

                spdlog::info("Добавлен новый счет: {}", account_name);

                return std::make_shared<AddAccountCommand>(account_name, db);
            }
            case 2: {
                return nullptr;
            }
            case 3: {
                return nullptr;
            }
            case 4: {
                return nullptr;
            }
            case 5: {
                return nullptr;
            }
            case 6: {
                return nullptr;
            }
            case 7: {
                return nullptr;
            }
            default:
                return nullptr;
        }
    }
};