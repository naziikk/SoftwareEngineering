#pragma once

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../infrastructure/database/database.h"

class BalanceProvider {
public:
    BalanceProvider(Database& db) : db_(db) {}

    long long get_balance(const std::string& user_id) {
        if (!check_account_existing(user_id)) {
            return LLONG_MIN;
        }

        std::vector<std::string> params = {user_id};
        std::string query = "SELECT money_amount FROM payments.bill WHERE user_id = $1";

        pqxx::result res = db_.execute_query(query, params);

        return res[0][0].as<long long>();
    }

    bool top_up_balance(const std::string& user_id, const std::string& amount) {
        if (!check_account_existing(user_id)) {
            return false;
        }

        std::string query = "UPDATE payments.bill SET money_amount = money_amount + $1 WHERE user_id = $2";
        std::vector<std::string> params = {amount, user_id};

        try {
            db_.execute_query(query, params);
        } catch (...) {
            return false;
        }

        return true;
    }

    bool check_account_existing(const std::string& user_id) {
        std::vector<std::string> params = {user_id};
        std::string query = "SELECT * FROM payments.bill WHERE user_id = $1";

        pqxx::result res = db_.execute_query(query, params);

        return !res.empty();
    }

private:
    Database& db_;
};