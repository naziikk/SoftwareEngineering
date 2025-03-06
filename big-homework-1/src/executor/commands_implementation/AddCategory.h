#include "../ProcessRequest.h"

class AddCategoryCommand : public Command {
public:
    AddCategoryCommand(std::string category_name, std::string category_type, DatabaseFacade& db)
            : category_name_(std::move(category_name)), category_type_(std::move(category_type)), db_(db) {}

    void Execute() override {
        if (CategoryExists(category_name_)) {
            spdlog::warn("Такая категория уже существует");
            return;
        }
        std::vector<std::string> params = {category_name_, category_type_};
        db_.ExecuteQuery("INSERT INTO finance_tracker.category (category_name, category_type) VALUES ($1, $2)",
                         params);
        spdlog::info("Добавлена новая категория: {}", category_name_);
    }

private:
    std::string category_name_;
    std::string category_type_;
    DatabaseFacade& db_;

    bool CategoryExists(const std::string& category_name) {
        std::vector<std::string> params = {category_name};
        return !db_.ExecuteQuery("SELECT 1 FROM finance_tracker.category WHERE category_name = $1",
                                 params).empty();
    }
};