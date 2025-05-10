#pragma once

#include <iostream>
#include <chrono>
#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"
#include "../utils.h"

void add_file_to_system(const httplib::Request& req, httplib::Response& res) {
    std::cout << "[REQUEST] Получен запрос на добавление файла в систему" << std::endl;
    auto start_time = std::chrono::steady_clock::now();
    std::string request_id;

    try {
        request_id = uuid::generate_uuid();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Ошибка при генерации UUID: " << e.what() << std::endl;
    }

    spdlog::info("[{}] Запрос на добавление файла в систему", request_id);

    if (req.files.empty()) {
        spdlog::warn("[{}] В запросе отсутствует файл", request_id);
        send_error(res, 400, "No file provided");
        return;
    }

    const auto& file = req.files.begin()->second;
    spdlog::info("[{}] Получен файл: имя = {}, тип = {}, размер = {} байт",
                 request_id, file.filename, file.content_type, file.content.size());

    httplib::Client api_gateway("http://storage:8007");
    api_gateway.set_connection_timeout(10);
    api_gateway.set_read_timeout(10);

    httplib::MultipartFormDataItems items = {
        {
            "file", file.content, file.filename, file.content_type
        }
    };

    spdlog::info("[{}] Отправка файла в сервис хранения по пути /file/upload", request_id);
    auto response = api_gateway.Post("/file/upload", items);

    if (response && response->status == 200) {
        try {
            nlohmann::json json_response = nlohmann::json::parse(response->body);
            spdlog::info("[{}] Успешная загрузка. Ответ: {} байт", request_id, response->body.size());
            res.status = 200;
            res.set_content(json_response.dump(), "application/json");
        } catch (const std::exception& e) {
            spdlog::error("[{}] Ошибка при парсинге JSON-ответа от сервиса хранения: {}", request_id, e.what());
            send_error(res, 500, "Invalid response from storage");
        }
    } else if (response) {
        spdlog::warn("[{}] Сервис хранения вернул ошибку: status {}, body: {}",
                     request_id, response->status, response->body);
        send_error(res, 400, "Error from storage: " + response->body);
    } else {
        spdlog::error("[{}] Не удалось подключиться к сервису хранения", request_id);
        send_error(res, 500, "Internal server error: no response from storage");
    }

    auto end_time = std::chrono::steady_clock::now();
    spdlog::debug("[{}] Обработка завершена за {} мс", request_id,
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
}