#pragma once
#include <iostream>
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
            std::cout << "Счет с таким именем уже существует\n";
        }
    }

private:
    std::string account_name_;
    DatabaseFacade& db_;
};

class AddCategoryCommand : public Command {
public:
    AddCategoryCommand(std::string category_name, DatabaseFacade& db) : category_name_(std::move(category_name)), db_(db) {}

    void Execute() override {
//        pqxx::result
    }

private:
    std::string category_name_;
    DatabaseFacade& db_;
};

class GetAccountsCommand : public Command {
public:
    GetAccountsCommand(DatabaseFacade& db) : db_(db) {}

    void Execute() override {
        std::cout << "Добавление нового счета\n";
    }

private:
    DatabaseFacade& db_;
};

class TopUpAccountCommand : public Command {
public:
    TopUpAccountCommand(std::string account_id, long long amount, DatabaseFacade& db)
    : account_id_(std::move(account_id)), amount_(amount), db_(db) {}

    void Execute() override {
        std::cout << "Добавление нового счета\n";
    }

private:
    std::string account_id_;
    long long amount_;
    DatabaseFacade& db_;
};