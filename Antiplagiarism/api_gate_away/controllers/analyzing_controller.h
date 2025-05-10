#pragma once

#include <iostream>
#include <chrono>
#include "../utils.h"
#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

#include "receiver_controller.h"

void get_analysis(const httplib::Request& req, httplib::Response& res) {
    auto start_time = std::chrono::steady_clock::now();
    std::string request_id = uuid::generate_uuid();

    spdlog::info("[{}] Запрос на анализ файла: {}", request_id, req.path_params.at("id"));

    get_file_content_request(req, res);
    if (res.status != 200) {
        spdlog::error("[{}] Не удалось получить файл: {}. Status: {}", request_id, res.body, res.status);
        send_error(res, 400, "Error from storage");
        return;
    }

    std::string document_id = extract_id_from_request(req);

    httplib::MultipartFormDataItems items = {
            {
                    "file", res.body, "file.txt"
            }
    };

    spdlog::debug("[{}] Получен document_id: {}", request_id, document_id);

    httplib::Client api_gateway("http://analyzer:8008");
    api_gateway.set_connection_timeout(10000000);
    api_gateway.set_read_timeout(100000000);
    api_gateway.set_default_headers({
            {"Accept", "application/json"}
    });

    spdlog::info("[{}] Отправка запроса на анализ файла в сервис анализа...", request_id);
    std::string path = "/file/" + document_id + "/analysis";
    auto response = api_gateway.Post(path, items);
//    std::cout << nlohmann::json::parse(response->body).dump() << std::endl;
//    if (response->status == 200) {
//        try {
    spdlog::info("[{}] Получен ответ от сервиса анализа", request_id);
    nlohmann::json json_response = nlohmann::json::parse(response->body);
    spdlog::info("[{}] Успешный анализ файла", request_id);
    res.status = 200;
    res.set_content(json_response.dump(), "application/json");
//        } catch (const std::exception& e) {
//            spdlog::error("[{}] Ошибка при разборе JSON от сервиса анализа: {}", request_id, e.what());
//            send_error(res, 500, "Invalid analysis service response");
//        }
//    } else if (response) {
//        spdlog::warn("[{}] Сервис анализа вернул ошибку: status {}, body: {}", request_id, response->status, response->body);
//        send_error(res, 400, "Error from analysis service");
//    } else {
//        spdlog::error("[{}] Не удалось связаться с сервисом анализа", request_id);
//        send_error(res, 500, "Internal server error");
//    }

    auto end_time = std::chrono::steady_clock::now();
    spdlog::debug("[{}] Анализ завершён за {} мс", request_id,
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
}

void get_words_cloud(const httplib::Request& req, httplib::Response& res) {
    auto start_time = std::chrono::steady_clock::now();
    std::string request_id = uuid::generate_uuid();

    std::string document_id = extract_id_from_request(req);
    spdlog::info("[{}] Запрос на облако слов по документу: {}", request_id, document_id);

    httplib::Client api("http://analyzer:8008");
    api.set_connection_timeout(10);
    api.set_read_timeout(10);
    api.set_default_headers({
            {"Content-Type", "application/json"},
            {"Accept", "application/json"}
    });
    std::string path = "/file/" + document_id + "/words_cloud";
    auto response = api.Get(path);

    if (response && response->status == 200) {
        try {
            nlohmann::json json_response = nlohmann::json::parse(response->body);
            spdlog::info("[{}] Успешное получение облака слов. Размер: {} байт", request_id, response->body.size());
            res.status = 200;
            res.set_content(json_response.dump(), "application/json");
        } catch (const std::exception& e) {
            spdlog::error("[{}] Ошибка при разборе JSON из облака слов: {}", request_id, e.what());
            send_error(res, 500, "Invalid word cloud response");
        }
    } else if (response) {
        spdlog::warn("[{}] Ошибка от сервиса анализа: status {}, body: {}", request_id, response->status, response->body);
        send_error(res, 400, "Error from analysis service");
    } else {
        spdlog::error("[{}] Не удалось подключиться к сервису анализа", request_id);
        send_error(res, 500, "Internal server error");
    }

    auto end_time = std::chrono::steady_clock::now();
    spdlog::debug("[{}] Получение облака слов завершено за {} мс", request_id,
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
}