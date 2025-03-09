#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../../database/decorator/Facade.h"

struct Transaction {
    std::string operation_type;
    std::string account_name;
    std::string category_name;
    double amount{};
    std::string date;
    std::string description;
};

std::vector<Transaction> ReadCSV(const std::string& filename) {
    std::vector<Transaction> transactions;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Ошибка при открытии файла\n";
        return {};
    }

    std::string line;
    bool header = true;

    while (std::getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }

        std::stringstream ss(line);
        Transaction transaction;
        std::string amount_str;

        std::getline(ss, transaction.operation_type, ',');

        if (transaction.operation_type != "INCOME" && transaction.operation_type != "EXPENSE") {
            continue;
        }

        std::getline(ss, transaction.account_name, ',');
        std::getline(ss, transaction.category_name, ',');
        std::getline(ss, amount_str, ',');
        std::getline(ss, transaction.date, ',');
        std::getline(ss, transaction.description, ',');

        try {
            transaction.amount = std::stod(amount_str);
            if (transaction.amount < 0) {
                continue;
            }
        } catch (...) {
            continue;
        }
        if (transaction.account_name.empty() || transaction.category_name.empty()
        || transaction.date.empty()) {
            continue;
        }

        transactions.push_back(transaction);
    }
    file.close();
    return transactions;
}

std::string GetCategoryId(const std::string& category_name, const std::string& category_type, DatabaseFacade& db) {
    std::vector<std::string> params = {category_name};
    pqxx::result response = db.ExecuteQuery("SELECT category_id FROM finance_tracker.category "
                                            "WHERE category_name = $1", params);

    if (!response.empty()) {
        return response[0][0].as<std::string>();
    }
    params.push_back(category_type);
    pqxx::result insert_response = db.ExecuteQuery(
            "INSERT INTO finance_tracker.category (category_name, category_type) VALUES ($1, $2) RETURNING category_id",
            params);

    return insert_response[0][0].as<std::string>();
}

std::string GetAccountId(const std::string& account_name, DatabaseFacade& db) {
    std::vector<std::string> params = {account_name};
    pqxx::result response = db.ExecuteQuery("SELECT account_id FROM finance_tracker.bank_account "
                                            "WHERE account_name = $1", params);

    if (!response.empty()) {
        return response[0][0].as<std::string>();
    }

    pqxx::result insert_response = db.ExecuteQuery(
            "INSERT INTO finance_tracker.bank_account (account_name, balance) VALUES ($1, 0) RETURNING account_id",
            params);

    return insert_response[0][0].as<std::string>();
}

static std::string AddOperation(Transaction transaction, const std::string& account_id,
                         const std::string& category_id, DatabaseFacade& db) {
    std::string insert_query = "INSERT INTO finance_tracker.operations (operation_type, bank_account_id, "
                               "category_id, amount, operation_date, description) "
                               "VALUES ($1, $2, $3, $4, $5, $6) RETURNING operation_id";
    std::vector<std::string> params = {transaction.operation_type, account_id, category_id,
                                       std::to_string(transaction.amount), transaction.date, transaction.description};

    return db.ExecuteQuery(insert_query, params)[0][0].as<std::string>();
}

static bool FillDatabase(const std::string& filename, DatabaseFacade& db) {
    std::vector<Transaction> transactions = ReadCSV(filename);
    if (transactions.empty()) {
        return false;
    }
    for (const auto& transaction : transactions) {
        std::string category_id = GetCategoryId(transaction.category_name, transaction.operation_type, db);
        std::string account_id = GetAccountId(transaction.account_name, db);

        std::string operation_id = AddOperation(transaction, account_id, category_id, db);

        if (operation_id.empty()) {
            return false;
        }
    }
    return true;
}