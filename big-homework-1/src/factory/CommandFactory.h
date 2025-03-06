#include <iostream>
#include "../executor/ProcessRequest.h"
#include "../executor/commands_implementation/AddCategory.h"
#include "../executor/commands_implementation/GetAccounts.h"
#include "../executor/commands_implementation/AddAccount.h"
#include "../executor/commands_implementation/TopUpAccount.h"
#include "../executor/commands_implementation/ApplyPayment.h"

class CommandFactory {
public:
    static std::shared_ptr<Command> CreateCommand(int choice, DatabaseFacade& db) {
        switch (choice) {
            case 1: {
                std::string account_name;
                std::cout << "Введите название счета: ";
                std::cin >> account_name;
                return std::make_shared<AddAccountCommand>(account_name, db);
            }
            case 2: {
                std::string category_name, category_type;
                std::cout << "Введите название категории: ";
                std::cin >> category_name;
                std::cout << "Введите тип категории (1 - доход | 2 - расход): ";
                int type;
                std::cin >> type;
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
                std::cout << "Введите идентификатор счета: ";
                std::string account_id;
                std::cin >> account_id;
                std::cout << "Введите сумму на которую хотите пополнить счет: ";
                long long amount;
                std::cin >> amount;

                return std::make_shared<TopUpAccountCommand>(account_id, amount, db);
            }
            case 5: {
                std::string account_name, category_name, description;
                long long amount;
                std::cout << "Введите название счета: ";
                std::cin >> account_name;
                std::cout << "Введите сумму операции: ";
                std::cin >> amount;
                std::cout << "Введите название категории: ";
                std::cin >> category_name;
                std::cout << "Введите описание операции: ";
                std::cin >> description;

                return std::make_shared<ApplyOperationCommand>(db, account_name, amount, category_name, description);
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