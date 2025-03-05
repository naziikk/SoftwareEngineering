#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <utility>
#include "../../database/migrations/Database.h"
#include <spdlog/spdlog.h>

class Command {
public:
    virtual void Execute() = 0;

    virtual ~Command() = default;
};

class AddAccountCommand : public Command {
public:
    AddAccountCommand(std::string account_name, DatabaseFacade& db) : account_name_(std::move(account_name)), db_(db) {}

    void Execute() override {
        std::string query = "SELECT * FROM finance_tracker.bank_account WHERE account_name = $1";
        std::vector<std::string> params = {account_name_};

        pqxx::result res = db_.ExecuteQuery(query, params);

        if (res.empty()) {
            query = "INSERT INTO finance_tracker.bank_account (account_name, balance) VALUES ($1, 0)";
            db_.ExecuteQuery(query, params);
            spdlog::info("Добавлен новый счет: {}", account_name_);
        } else {
            spdlog::warn("Счет с таким названием уже существует");
            std::cout << "Счет с таким названием уже существует\n";
        }
    }

private:
    std::string account_name_;
    DatabaseFacade& db_;
};

class AddCategoryCommand : public Command {
public:
    AddCategoryCommand(std::string category_name, std::string category_type, DatabaseFacade& db)
        : category_name_(std::move(category_name)), db_(db), category_type_(std::move(category_type)) {}

    void Execute() override {
        std::string query = "SELECT * FROM finance_tracker.category WHERE category_name = $1";
        std::vector<std::string> params = {category_name_};

        pqxx::result res = db_.ExecuteQuery(query, params);

        if (res.empty()) {
            query = "INSERT INTO finance_tracker.category (category_name, category_type) VALUES ($1, $2)";
            params.push_back(category_type_);
            db_.ExecuteQuery(query, params);
            spdlog::info("Добавлена новая категория: {}", category_name_);
        } else {
            spdlog::warn("Такая категория уже существует");
            std::cout << "Такая категория уже существует\n";
        }
    }

private:
    std::string category_name_;
    std::string category_type_;
    DatabaseFacade& db_;
};

class GetAccountsCommand : public Command {
public:
    GetAccountsCommand(DatabaseFacade& db) : db_(db) {}

    void Execute() override {
        std::string query = "SELECT * FROM finance_tracker.bank_account";
        std::vector<std::string> params;
        pqxx::result rows = db_.ExecuteQuery(query, params);

        for (const auto& row : rows) {
            std::cout << "Счет: " << row["account_name"].c_str() << ", id счета: " << row["id"].c_str() << '\n';
        }
        spdlog::info("Возвращен список банковских счетов");
    }

private:
    DatabaseFacade& db_;
};

class TopUpAccountCommand : public Command {
public:
    TopUpAccountCommand(std::string account_id, long long amount, DatabaseFacade& db)
    : account_id_(std::move(account_id)), amount_(amount), db_(db) {}

    void Execute() override {
        if (amount_ <= 0) {
            spdlog::warn("Сумма должна быть положительной");
            std::cout << "Сумма должна быть положительной\n";
            return;
        }

        std::string query = "SELECT * FROM finance_tracker.bank_account WHERE id = $1";
        std::vector<std::string> params = {account_id_};

        pqxx::result res = db_.ExecuteQuery(query, params);

        if (res.empty()) {
            spdlog::warn("Счет с таким id не найден");
            std::cout << "Счет с таким id не найден\n";
            return;
        }

        query = "UPDATE finance_tracker.bank_account SET balance = balance + $1 WHERE id = $2";
        params = {std::to_string(amount_), account_id_};
        db_.ExecuteQuery(query, params);

        spdlog::info("Счет {} пополнен на {}", account_id_, amount_);
    }

private:
    std::string account_id_;
    long long amount_;
    DatabaseFacade& db_;
};
