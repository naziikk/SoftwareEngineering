#include "../ProcessRequest.h"

class AddAccountCommand : public Command {
public:
    AddAccountCommand(std::string account_name, DatabaseFacade& db)
            : account_name_(std::move(account_name)), db_(db) {}

    void Execute() override {
        if (AccountExists(account_name_)) {
            spdlog::warn("Счет с таким названием уже существует");
            return;
        }
        std::vector<std::string> params = {account_name_};
        db_.ExecuteQuery("INSERT INTO finance_tracker.bank_account (account_name, balance) VALUES ($1, 0)",
                         params);
        spdlog::info("Добавлен новый счет: {}", account_name_);
    }

private:
    std::string account_name_;
    DatabaseFacade& db_;

    bool AccountExists(const std::string& account_name) {
        std::vector<std::string> params = {account_name};
        return !db_.ExecuteQuery("SELECT 1 FROM finance_tracker.bank_account WHERE account_name = $1",
                                 params).empty();
    }
};