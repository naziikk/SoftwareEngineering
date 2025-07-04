#include "third_party/httplib.h"

#include "infrastructure/database/database.h"
#include "infrastructure/config/config.h"
#include "infrastructure/kafka/workers/order_to_pay_consumer.h"
#include "infrastructure/kafka/workers/order_status_consumer.h"

#include "controllers/account_crud_controller.h"

#include "app/account_balance.h"
#include "app/account_creator.h"

int main() {
    httplib::Server server;

    server.Options(".*", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Origin", "http://localhost:8009");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        res.status = 200;
    });

    auto set_cors_headers = [&](httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:8009");
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    };

    Config cfg = Config::MustLoadConfig("infrastructure/config/config.yaml");
    std::string connection = "dbname=" + cfg.database_.db_name + " host=" + cfg.database_.host + " port=" + std::to_string(cfg.database_.port) +
                             " user=" + cfg.database_.user + " password=" + cfg.database_.password;
    Database db(connection);
    db.init_db_from_file("infrastructure/database/payments_storage.sql");

    KafkaProducer producer("kafka:9092", "orders_status");

    // --------------------------------------------Основные обработчики-------------------------------------------------
    OrdersToPayConsumer consumer;
    consumer.listen_orders_to_pay_topic(db);
    start_outbox_processor(db, producer);
    // -----------------------------------------------------------------------------------------------------------------

    AccountCreator account_creator(db);
    BalanceProvider balance_provider(db);

    AccountCrudController controller(account_creator, balance_provider);

    server.Post("/account", [&db, &set_cors_headers, &controller](const httplib::Request& request, httplib::Response &res) {
        std::cout << "CЮДА ДОШЛИ, ХОТИМ СОЗДАТЬ АККАУНТ\n";
        set_cors_headers(res);
        controller.create_account_request(request, res);
    });

    server.Get("/account/:id/balance", [&db, &set_cors_headers, &controller](const httplib::Request& request, httplib::Response &res) {
        std::cout << "CЮДА ДОШЛИ, ХОТИМ ПОСМОТРЕТЬ БАЛАНС АККАУНТА\n";
        set_cors_headers(res);
        controller.get_account_balance_request(request, res);
    });

    server.Post("/account/top_up", [&db, &set_cors_headers, &controller](const httplib::Request& request, httplib::Response &res) {
        std::cout << "CЮДА ДОШЛИ, ХОТИМ ПОПОЛНИТЬ БАЛАНС АККАУНТА\n";
        set_cors_headers(res);
        controller.account_top_up_request(request, res);
    });

    server.listen(cfg.server_.host, cfg.server_.port);
}