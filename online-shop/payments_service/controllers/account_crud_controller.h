#pragma once

#include "../utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

#include "../app/account_balance.h"
#include "../app/account_creator.h"

class AccountCrudController {
public:
    AccountCrudController(AccountCreator& creator, BalanceProvider& provider)
    : account_creator_(creator), balance_provider_(provider) {}

    void get_account_balance_request(const httplib::Request& req, httplib::Response& res);

    void create_account_request(const httplib::Request& req, httplib::Response& res);

    void account_top_up_request(const httplib::Request& req, httplib::Response& res);

private:
    using json = nlohmann::json;

    AccountCreator account_creator_;
    BalanceProvider balance_provider_;
};

