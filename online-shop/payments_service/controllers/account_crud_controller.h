#include "utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

class AccountCrudController {
public:
    AccountCrudController() = default;

    void get_account_balance_request(const httplib::Response& res, httplib::Response& res);

    void create_account_request(const httplib::Response& res, httplib::Response& res);

private:
    using json = nlohmann::json;
};

