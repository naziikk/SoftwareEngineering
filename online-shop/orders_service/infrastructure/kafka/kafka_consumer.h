#pragma once

#include <cppkafka/cppkafka.h>
#include <functional>
#include <string>

class KafkaConsumer {
public:
    KafkaConsumer(const std::string& brokers, const std::string& topic, const std::string& group_id);

    void consume(std::function<void(const std::string&)> callback);

private:
    cppkafka::Configuration config_;
    cppkafka::Consumer consumer_;
};