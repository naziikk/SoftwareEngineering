#include "utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

class OrdersOperationsController {
public:
    void get_orders_request(const httplib::Request& req, httplib::Response& res) {

    }

    void get_order_info_request(const httplib::Request& req, httplib::Response& res) {

    }

private:
    using json = nlohmann::json;
};