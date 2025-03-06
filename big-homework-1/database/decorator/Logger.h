#include "Decorator.h"
#include <spdlog/spdlog.h>

class LoggingDatabaseDecorator : public DatabaseDecorator {
public:
    explicit LoggingDatabaseDecorator(std::shared_ptr<IDatabase> database) : DatabaseDecorator(std::move(database)) {}

    pqxx::result ExecuteQuery(const std::string& query, const std::vector<std::string>& params) override {
        spdlog::info("Выполняется запрос: {} с параметрами: [{}]", query, fmt::join(params, ", "));

        auto result = db_->ExecuteQuery(query, params);
        spdlog::info("Запрос успешно выполнен.");

        return result;
    }
};