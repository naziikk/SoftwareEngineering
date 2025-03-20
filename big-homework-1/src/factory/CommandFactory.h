#include <iostream>
#include "../DI-container.h"
#include "../exporter/SaveData.h"
#include "../executor/ProcessRequest.h"
#include "../executor/commands_implementation/AddCategory.h"
#include "../executor/commands_implementation/AddAccount.h"
#include "../executor/commands_implementation/ApplyPayment.h"
#include "../executor/commands_implementation/GetAccounts.h"
#include "../executor/commands_implementation/TopUpAccount.h"
#include "../executor/commands_implementation/DeleteAccount.h"
#include "../executor/commands_implementation/GetCategories.h"

std::string HelperStringEnter(const std::string& message) {
    std::cout << message;
    std::string entered;
    std::cin >> entered;
    return entered;
}

int HelperIntEnter(std::string message) {
    std::cout << message;
    int entered;
    std::cin >> entered;
    return entered;
}

class CommandFactory {
public:
    static std::shared_ptr<Command> CreateCommand(int choice, DatabaseFacade& db) {
        switch (choice) {
            case 1: {
                std::string account_name = HelperStringEnter("Введите название счета: ");
                return std::make_shared<AddAccountCommand>(account_name, db);
            }
            case 2: {
                std::string category_type;
                std::string category_name = HelperStringEnter("Введите название категории: ");
                int type = HelperIntEnter("Введите тип категории (1 - доход, 2 - расход): ");

                if (type == 1) {
                    category_type = "INCOME";
                } else if (type == 2) {
                    category_type = "EXPENSE";
                }

                return std::make_shared<AddCategoryCommand>(category_name, category_type, db);
            }
            case 3: {
                return std::make_shared<GetAccountsCommand>(db);
            }
            case 4: {
                std::string account_id = HelperStringEnter("Введите название счета: ");
                long long amount = HelperIntEnter("Введите сумму пополнения: ");

                return std::make_shared<TopUpAccountCommand>(account_id, amount, db);
            }
            case 5: {
                std::string account_name = HelperStringEnter("Введите название счета: ");
                std::string category_name = HelperStringEnter("Введите название категории: ");
                std::string description = HelperStringEnter("Введите описание операции: ");
                long long amount = HelperIntEnter("Введите сумму операции: ");

                return std::make_shared<ApplyOperationCommand>(db, account_name, amount, category_name, description);
            }
            case 6: {
                std::string format = HelperStringEnter("Выберите формат выходного файла (1 - JSON, 2 - YAML, 3 - CSV): ");
                std::string filename = HelperStringEnter("Введите название файла: ");
                std::string account_name = HelperStringEnter("Введите название счета по которому хотите получить выгрузку: ");
                std::string last_time_min = HelperStringEnter("За сколько последних минут? (введите 0, если не важно): ");

                if (std::stoi(format) == 1) {
                    JSONFileSaver json_saver;
                    json_saver.Export(filename, account_name, last_time_min, db);
                } else if (std::stoi(format) == 2) {
                    YAMLFileSaver yaml_saver;
                    yaml_saver.Export(filename, account_name, last_time_min, db);
                } else {
                    CSVFileSaver csv_saver;
                    csv_saver.Export(filename, account_name, last_time_min, db);
                }
            }
            case 7: {
                std::string account_name = HelperStringEnter("Введите название счета: ");
                return std::make_shared<DeleteAccountCommand>(db, account_name);
            }
            case 8: {
                return std::make_shared<GetCategoriesCommand>(db);
            }
            default:
                return nullptr;
        }
    }
};