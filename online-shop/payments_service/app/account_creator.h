#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../infrastructure/database/database.h"

class AccountCreator {
public:
    AccountCreator(Database& db) : db_(db) {}

    bool create_account(const std::string& user_id) {
        if (check_account_existing(user_id)) {
            return false;
        }

        std::string query = "INSERT INTO payments.bill (user_id, money_amount) VALUES ($1, $2)";
        std::vector<std::string> params = {user_id, 0};

        try {
            db_->execute_query(query, params);
        } catch (...) {
            return false;
        }

        return true;
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