#include <iostream>
#include "../kafka_consumer.h"
#include "../../database/database.h"
#include "../../../third_party/nlohmann/json.hpp"

class OrdersToPayConsumer {
public:
    void listen_orders_to_pay_topic(Database& db) {
        std::thread consumer_thread([this, &db]() {
            KafkaConsumer consumer("localhost:9092", "orders_to_pay", "orders_group");

            while (true) {
                try {
                    consumer.consume([this, &db](const std::string& msg) {
                        std::cout << "Получили заказ в Kafka: " << msg << '\n';

                        nlohmann::json order_info = nlohmann::json::parse(msg);

                        std::string user_id = order_info["user_id"].get<std::string>();
                        std::string amount = order_info["amount"].get<std::string>();
                        std::string description = order_info["description"].get<std::string>();
                        std::string order_id = order_info["id"].get<std::string>();

                        if (!check_account_exists(db, user_id)) {
                            std::cerr << "Аккаунт с user_id: " << user_id << " не найден." << std::endl;
                            save_order_status(order_id, "FAILED", db);
                            return;
                        }

                        if (!check_balance_consistency(db, user_id, amount)) {
                            std::cerr << "Недостаточно средств на балансе для user_id: " << user_id << std::endl;
                            save_order_status(order_id, "FAILED", db);
                            return;
                        }

                        update_balance(db, user_id, amount);
                        save_order_status(order_id, "SUCCESS", db);
                    });
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка при чтении из Kafka: " << e.what() << '\n';
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
        });

        consumer_thread.detach();
    }

private:
    bool check_account_exists(Database& db, const std::string& user_id) {
        std::string query = "SELECT * FROM payments.bill WHERE user_id = $1";
        std::vector<std::string> params = {user_id};
        pqxx::result res = db.execute_query(query, params);

        return !res.empty();
    }

    void save_order_status(const std::string& order_id, const std::string& status, Database& db) {
        std::string update_query = "INSERT INTO payments.outbox(order_id, status) VALUES ($1, $2)";

        std::vector<std::string> params = {order_id, status};

        try {
            db.execute_query(update_query, params);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при обновлении статуса заказа: " << e.what() << '\n';
        }
    }

    bool check_balance_consistency(Database& db, const std::string& user_id, const std::string& amount) {
        std::string query = "SELECT balance FROM payments.bill WHERE user_id = $1";
        std::vector<std::string> params = {user_id};
        pqxx::result res = db.execute_query(query, params);

        if (res.empty()) {
            std::cerr << "Аккаунт с user_id: " << user_id << " не найден." << std::endl;
            return false;
        }

        double balance = res[0]["balance"].as<double>();
        double order_amount = std::stod(amount);

        return balance >= order_amount;
    }

    void update_balance(Database& db, const std::string& user_id, const std::string& amount) {
        std::string query = "UPDATE payments.bill SET balance = balance - $1 WHERE user_id = $2";
        std::vector<std::string> params = {amount, user_id};

        try {
            db.execute_query(query, params);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при обновлении : " << e.what() << '\n';
        }
    }
};