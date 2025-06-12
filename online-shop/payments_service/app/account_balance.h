#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../infrastructure/database/database.h"

class BalanceProvider {
public:
    BalanceProvider(Database& db) : db_(db) {}

    long long get_balance(const std::string& user_id) {
        if (check_account_existing(user_id)) {
            return LLONG_MIN;
        }

        std::vector<std::string> params = {user_id};
        std::string query = "SELECT money_amount FROM payments.bill WHERE user_id = $1";

        pqxx::result res = db_->execute_query(query, params);

        return res[0][0].as<long long>();
    }

    bool check_account_existing(const std::string& user_id) {
        std::vector<std::string> params = {user_id};
        std::string query = "SELECT * FROM payments.bill WHERE user_id = $1";

        pqxx::result res = db_->execute_query(query, params);

        return !res.empty();
    }

private:
    Database& db_;
};