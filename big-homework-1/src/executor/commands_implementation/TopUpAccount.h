#include "../ProcessRequest.h"
#pragma once

class TopUpAccountCommand : public Command {
public:
    TopUpAccountCommand(std::string account_name, long long amount, DatabaseFacade& db)
            : account_name_(std::move(account_name)), amount_(amount), db_(db) {}

    void Execute() override {
        if (amount_ <= 0) {
            spdlog::warn("Сумма должна быть положительной");
            return;
        }

        if (!AccountExists(account_name_)) {
            spdlog::warn("Счет с таким ID не найден");
            return;
        }
        std::vector<std::string> params = {std::to_string(amount_), account_name_};
        db_.ExecuteQuery("UPDATE finance_tracker.bank_account SET balance = balance + $1 WHERE account_name = $2",
                         params);
        spdlog::info("Счет {} пополнен на {}", account_name_, amount_);
    }

private:
    std::string account_name_;
    long long amount_;
    DatabaseFacade& db_;

    bool AccountExists(const std::string& account_name) {
        std::vector<std::string> params = {account_name};
        return !db_.ExecuteQuery("SELECT 1 FROM finance_tracker.bank_account WHERE account_name = $1",
                                 params).empty();
    }
};