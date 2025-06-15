#include "kafka_consumer.h"
#include <iostream>

KafkaConsumer::KafkaConsumer(const std::string& brokers, const std::string& topic, const std::string& group_id)
        : config_({
                  {"metadata.broker.list", brokers},
                  {"group.id", group_id},
                  {"enable.auto.commit", false}
        }), consumer_(config_) {
    consumer_.subscribe({topic});
}

void KafkaConsumer::consume(std::function<void(const std::string&)> callback) {
    while (true) {
        auto msg = consumer_.poll();
        if (msg) {
            if (!msg.get_error()) {
                callback(msg.get_payload());
                consumer_.commit(msg);
            } else {
                std::cerr << "Ошибка получателя: " << msg.get_error() << std::endl;
            }
        }
    }
}
