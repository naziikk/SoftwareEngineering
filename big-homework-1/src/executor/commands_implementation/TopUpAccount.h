#include "../ProcessRequest.h"

class TopUpAccountCommand : public Command {
public:
    TopUpAccountCommand(std::string account_id, long long amount, DatabaseFacade& db)
            : account_id_(std::move(account_id)), amount_(amount), db_(db) {}

    void Execute() override {
        if (amount_ <= 0) {
            spdlog::warn("Сумма должна быть положительной");
            return;
        }

        if (!AccountExists(account_id_)) {
            spdlog::warn("Счет с таким ID не найден");
            return;
        }
        std::vector<std::string> params = {std::to_string(amount_), account_id_};
        db_.ExecuteQuery("UPDATE finance_tracker.bank_account SET balance = balance + $1 WHERE account_id = $2",
                         params);
        spdlog::info("Счет {} пополнен на {}", account_id_, amount_);
    }

private:
    std::string account_id_;
    long long amount_;
    DatabaseFacade& db_;

    bool AccountExists(const std::string& account_id) {
        std::vector<std::string> params = {account_id};
        return !db_.ExecuteQuery("SELECT 1 FROM finance_tracker.bank_account WHERE account_id = $1",
                                 params).empty();
    }
};