#include "../ProcessRequest.h"

class DeleteAccountCommand : public Command {
public:
    DeleteAccountCommand(DatabaseFacade& db, std::string account_name)
            : db_(db), account_name_(std::move(account_name)) {}

    void Execute() override {
        if (!CheckAccountExistence()) {
            spdlog::warn("Счет с именем '{}' не найден", account_name_);
            return;
        }

        DeleteAccount();
        spdlog::info("Счет '{}' успешно удален", account_name_);
    }

private:
    bool CheckAccountExistence() {
        std::vector<std::string> params = {account_name_};
        return !db_.ExecuteQuery("SELECT 1 FROM finance_tracker.bank_account WHERE account_name = $1", params).empty();
    }

    void DeleteAccount() {
        std::vector<std::string> params = {account_name_};
        db_.ExecuteQuery("DELETE FROM finance_tracker.bank_account WHERE account_name = $1", params);
    }

    DatabaseFacade& db_;
    std::string account_name_;
};