#include "../ProcessRequest.h"

class GetAccountsCommand : public Command {
public:
    GetAccountsCommand(DatabaseFacade& db) : db_(db) {}

    void Execute() override {
        std::vector<std::string> params;
        pqxx::result rows = db_.ExecuteQuery("SELECT * FROM finance_tracker.bank_account", params);

        for (const auto& row : rows) {
            std::cout << "Счет: " << row["account_name"].c_str() <<
            ", id счета: " << row["account_id"].c_str() <<
            ", баланс: " << row["balance"].c_str() << '\n';
        }
        spdlog::info("Возвращен список банковских счетов");
    }

private:
    DatabaseFacade& db_;
};