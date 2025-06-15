#include "kafka_producer.h"

KafkaProducer::KafkaProducer(const std::string& brokers, const std::string& topic)
        : config_({ {"bootstrap.servers", brokers} }), producer_(config_), topic_(topic) {}

void KafkaProducer::send(const std::string& message) {
    producer_.produce(cppkafka::MessageBuilder(topic_).partition(0).payload(message));
    producer_.flush();
}