#include "../ProcessRequest.h"
#pragma once

class ApplyOperationCommand : public Command {
public:
    enum class TransactionType { INCOME, EXPENSE };

    ApplyOperationCommand(DatabaseFacade& db, std::string account_name, long long amount,
                          std::string category_name, std::string description)
            : db_(db), account_name_(std::move(account_name)), amount_(amount),
              category_name_(std::move(category_name)), description_(std::move(description)) {}

    void Execute() override {
        try {
            category_id_ = GetCategoryId();
            account_id_ = GetAccountId();
            TransactionType type = GetCategoryType();

            if (type == TransactionType::EXPENSE && !CheckBalance()) {
                spdlog::warn("На счете {} недостаточно средств", account_name_);
                std::cout << "На счете недостаточно средств\n";
                return;
            }

            RecordOperation(type);
            UpdateBalance(type);

            spdlog::info("Операция успешно зафиксирована, баланс счета обновлен");
        } catch (const std::exception& e) {
            spdlog::error("Ошибка при выполнении операции: {}", e.what());
            std::cout << "Ошибка при выполнении операции\n";
        }
    }

private:
    DatabaseFacade& db_;
    std::string account_name_;
    std::string category_name_;
    std::string category_id_;
    std::string account_id_;
    std::string description_;
    long long amount_;

    std::string GetCategoryId() {
        std::string query = "SELECT category_id FROM finance_tracker.category WHERE category_name = $1";
        std::vector<std::string> params = {category_name_};
        pqxx::result res = db_.ExecuteQuery(query, params);

        if (res.empty()) {
            throw std::runtime_error("Категория не найдена: " + category_name_);
        }
        return res[0]["category_id"].as<std::string>();
    }

    std::string GetAccountId() {
        std::string query = "SELECT account_id FROM finance_tracker.bank_account WHERE account_name = $1";
        std::vector<std::string> params = {account_name_};
        pqxx::result res = db_.ExecuteQuery(query, params);

        if (res.empty()) {
            throw std::runtime_error("Счет не найден: " + account_name_);
        }
        return res[0]["account_id"].as<std::string>();
    }

    TransactionType GetCategoryType() {
        std::string query = "SELECT category_type FROM finance_tracker.category WHERE category_id = $1";
        std::vector<std::string> params = {category_id_};
        pqxx::result res = db_.ExecuteQuery(query, params);

        std::string type = res[0]["category_type"].as<std::string>();
        return (type == "EXPENSE") ? TransactionType::EXPENSE : TransactionType::INCOME;
    }

    bool CheckBalance() {
        std::string query = "SELECT balance FROM finance_tracker.bank_account WHERE account_id = $1";
        std::vector<std::string> params = {account_id_};
        pqxx::result res = db_.ExecuteQuery(query, params);

        std::string balance = res[0]["balance"].as<std::string>();
        long long balance_ll = std::stoll(balance);
        return balance_ll >= amount_;
    }

    void RecordOperation(TransactionType type) {
        std::string query = "INSERT INTO finance_tracker.operations (operation_type, bank_account_id, category_id, amount, description) VALUES ($1, $2, $3, $4, $5)";
        std::vector<std::string> params = {type == TransactionType::EXPENSE ? "EXPENSE" : "INCOME",
                                           account_id_, category_id_, std::to_string(amount_), description_};
        db_.ExecuteQuery(query, params);
    }

    void UpdateBalance(TransactionType type) {
        std::string query = "UPDATE finance_tracker.bank_account SET balance = balance "
                            + std::string(type == TransactionType::EXPENSE ? "- " : "+ ") + "$1 WHERE account_id = $2";
        std::vector<std::string> params = {std::to_string(amount_), account_id_};
        db_.ExecuteQuery(query, params);
    }
};