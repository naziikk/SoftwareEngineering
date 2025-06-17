#!/bin/bash

KAFKA_BROKER="kafka:9092"

TOPICS=(
  "orders_status:1:1"
  "orders_to_pay:1:1"
)

echo "Ожидаем запуска Kafka..."
while ! nc -z kafka 9092; do
  sleep 1
done

echo "Kafka запущена, создаем топики..."

for topic in "${TOPICS[@]}"; do
  IFS=":" read -r NAME PARTITIONS REPL_FACTOR <<< "$topic"

  kafka-topics \
    --bootstrap-server "$KAFKA_BROKER" \
    --create \
    --if-not-exists \
    --topic "$NAME" \
    --partitions "$PARTITIONS" \
    --replication-factor "$REPL_FACTOR"

  echo "Создан топик: $NAME"
done
