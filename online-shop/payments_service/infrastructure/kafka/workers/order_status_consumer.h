#include <vector>
#include "../kafka_producer.h"
#include "../../database/database.h"

void start_outbox_processor(Database& db, KafkaProducer& producer) {
    std::thread([&db, &producer]() {
        while (true) {
            try {
                std::string select_query = "SELECT id, order_id, status FROM payments.outbox WHERE sending_status = $1";
                std::vector<std::string> params = {"NOT_SENT"};
                auto results = db.execute_query(select_query, params);

                for (const auto& row : results) {
                    std::string order_id = row["order_id"].as<std::string>();
                    std::string status = row["status"].as<std::string>();
                    std::string id = row["id"].as<std::string>();

                    nlohmann::json message = {
                            {"order_id", order_id},
                            {"status", status}
                    };

                    producer.send(message.dump());

                    std::string update_query =
                            "UPDATE payments.outbox SET sending_status = 'SENT' WHERE id = $1";
                    std::vector<std::string> update_params = {id};
                    db.execute_query(update_query, update_params);
                }

            } catch (const std::exception& e) {
                std::cerr << "Ошибка в Outbox обработчике: " << e.what() << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }).detach();
}