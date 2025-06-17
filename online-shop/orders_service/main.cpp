#include "third_party/httplib.h"
#include "infrastructure/database/database.h"
#include "infrastructure/config/config.h"

#include "controllers/get_orders_controller.h"
#include "controllers/create_order_controller.h"
#include "app/orders.h"

#include "infrastructure/kafka/kafka_consumer.h"
#include <thread>
#include "utils.h"

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
    db.init_db_from_file("infrastructure/database/orders_storage.sql");

    Orders orders(db);
    GetOrdersController controller(orders);
    OrderCreatingController creating_controller(db);

    KafkaProducer producer("kafka:9092", "orders_to_pay");

    // --------------------------------------------Основные обработчики--------------------------------------------------
    start_outbox_processor(db, producer);

    std::thread consumer_thread([&]() {
        KafkaConsumer consumer("kafka:9092", "orders_to_pay", "orders_group");
        consumer.consume([&](const std::string& msg) {
            std::cout << "Получили заказ в Kafka: " << msg << '\n';

            std::string request = "INSERT INTO orders_storage.orders (user_id, description, amount) VALUES ($1, $2, $3)";
            nlohmann::json order_ = nlohmann::json::parse(msg);
            std::vector<std::string> params = {order_["user_id"], order_["description"], order_["amount"]};

            try {
                db.execute_query(request, params);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при выполнении запроса: " << e.what() << '\n';

            }
        });
    });

    std::thread consumer_order_status_thread([&]() {
        KafkaConsumer consumer("kafka:9092", "orders_status", "orders_status_group");
        consumer.consume([&](const std::string& msg) {
            std::cout << "Получили статус заказа в Kafka: " << msg << '\n';

            nlohmann::json order_status = nlohmann::json::parse(msg);
            std::string order_id = order_status["order_id"];
            std::string status = order_status["status"];

            std::string update_query = "UPDATE orders_storage.orders SET status = $1 WHERE id = $2";
            std::vector<std::string> params = {status, order_id};

            try {
                db.execute_query(update_query, params);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при обновлении статуса заказа: " << e.what() << '\n';
            }
        });
    });

    // -------------------------------------------------------------------------------------------------------------------

    server.Get("/orders/:id/list", [&db, &set_cors_headers, &controller](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        controller.get_orders_request(request, res);
    });

    server.Post("/orders/:id", [&db, &set_cors_headers, &controller](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        controller.get_order_by_id_request(request, res);
    });

    server.Post("/order/create", [&db, &set_cors_headers, &creating_controller](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        creating_controller.create_order_request(request, res);
    });


    consumer_thread.detach();

    server.listen(cfg.server_.host, cfg.server_.port);
}