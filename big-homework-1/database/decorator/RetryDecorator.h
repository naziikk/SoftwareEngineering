#include "Decorator.h"
#include <spdlog/spdlog.h>

class RetryDatabaseQueryDecorator : public DatabaseDecorator {
public:
    explicit RetryDatabaseQueryDecorator(std::shared_ptr<IDatabase> database, int max_retries)
    : DatabaseDecorator(std::move(database)), max_retries_(max_retries) {}

    pqxx::result ExecuteQuery(const std::string& query, const std::vector<std::string>& params) override {
        int attempts = 0;
        while (attempts < max_retries_) {
            try {
                return db_->ExecuteQuery(query, params);
            } catch (const std::exception& e) {
                spdlog::warn("Запрос не выполнился (попытка {}/{}): {}. Пробуем снова...", attempts + 1, max_retries_, e.what());
                ++attempts;
            }
        }
        spdlog::error("Не удалось выполнить запрос после нескольких попыток");
        return pqxx::result{};
    }

private:
    int max_retries_;
};