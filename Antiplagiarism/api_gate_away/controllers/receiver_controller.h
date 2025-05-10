#pragma once

#include <chrono>
#include <iostream>
#include "../utils.h"
#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

void get_file_content_request(const httplib::Request& req, httplib::Response& res) {
    auto start_time = std::chrono::steady_clock::now();
    std::string request_id = uuid::generate_uuid();

    std::string document_id = extract_id_from_request(req);
    spdlog::info("[{}] Запрос на получение содержимого файла: {}", request_id, document_id);

    httplib::Client api("http://storage:8007");
    api.set_connection_timeout(10);
    api.set_read_timeout(10);
    api.set_default_headers({
            {"Accept", "text/plain"}
    });

    std::string path = "/file/" + document_id;
    spdlog::debug("[{}] Отправка GET запроса на {}", request_id, path);

    auto response = api.Get(path);

    if (response && response->status == 200) {
        spdlog::info("[{}] Успешно получено содержимое файла. Размер: {} байт", request_id, response->body.size());
        res.status = 200;
        res.set_content(response->body, "text/plain");
        res.set_header("Content-Disposition", "attachment; filename=\"" + document_id + ".txt\"");
    } else if (response) {
        spdlog::warn("[{}] Хранилище вернуло ошибку: status {}, body: {}", request_id, response->status, response->body);
        send_error(res, 400, "Error from storage");
    } else {
        spdlog::error("[{}] Не удалось подключиться к сервису хранилища", request_id);
        send_error(res, 500, "Internal server error");
    }

    auto end_time = std::chrono::steady_clock::now();
    spdlog::debug("[{}] Получение содержимого файла завершено за {} мс", request_id,
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
}