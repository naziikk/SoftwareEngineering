#pragma once
#include "../utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../app/orders.h"

class GetOrdersController {
public:
    GetOrdersController(Orders& order_service) : orders_service_(order_service) {};

    void get_orders_request(const httplib::Request& req, httplib::Response& res);

    void get_order_by_id_request(const httplib::Request& req, httplib::Response& res);

private:
    using json = nlohmann::json;

    Orders& orders_service_;
};
