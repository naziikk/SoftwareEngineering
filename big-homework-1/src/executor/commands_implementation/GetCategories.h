#include "../ProcessRequest.h"
#include <spdlog/spdlog.h>
#include <iostream>

class GetCategoriesCommand : public Command {
public:
    explicit GetCategoriesCommand(DatabaseFacade& db) : db_(db) {}

    void Execute() override {
        pqxx::result rows = db_.ExecuteQuery("SELECT * FROM finance_tracker.category", {});

        if (rows.empty()) {
            spdlog::warn("Категории не найдены.");
            return;
        }

        spdlog::info("Возвращен список категорий:");
        for (const auto& row : rows) {
            std::cout << "Категория: " << row["category_name"].c_str()
                      << ", Тип: " << row["category_type"].c_str()
                      << ", ID: " << row["category_id"].c_str() << '\n';
        }
    }

private:
    DatabaseFacade& db_;
};