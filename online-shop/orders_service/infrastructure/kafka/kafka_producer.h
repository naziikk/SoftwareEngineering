#pragma once
#include <cppkafka/cppkafka.h>

class KafkaProducer {
public:
    KafkaProducer(const std::string& brokers, const std::string& topic);

    void send(const std::string& message);

private:
    cppkafka::Configuration config_;
    cppkafka::Producer producer_;
    std::string topic_;
};


