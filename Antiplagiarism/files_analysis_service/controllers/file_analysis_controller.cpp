#include "file_analysis_controller.h"

void FileAnalyseController::file_analysis_request(const httplib::Request& req, httplib::Response& res) {
    if (!is_valid_id(req)) {
        handle_empty_or_incorrect_id("id", res);
        return;
    }
    std::cout << "[REQUEST]  валидный idшник " << std::endl;
    std::string document_id = extract_id_from_request(req);
    if (is_in_analysis_history(document_id)) {
        json analysis = get_file_analysis(document_id);

        res.status = 200;
        res.set_content(analysis.dump(), "application/json");

        return;
    }
    std::cout << "[REQUEST] не найден в истории анализа " << std::endl;
    std::cout << req.files.size() << '\n';
    const auto& file = req.files.begin()->second;
//    httplib::MultipartFormData file = req.get_file_value(req.files[0].name);
    std::cout << "[REQUEST] получен файл: имя = " << file.filename << ", тип = " << file.content_type << ", размер = " << file.content.size() << " байт" << std::endl;
    analyzer_.analyse_file(file, document_id);
    std::cout << "[REQUEST] файл проанализирован" << std::endl;
    if (is_in_analysis_history(document_id)) {
        std::cout << "[REQUEST] файл найден в истории анализа" << std::endl;
        json analysis = get_file_analysis(document_id);
        std::cout << "[REQUEST] файл найден в истории анализа, id = " << document_id << std::endl;
        std::cout << "[REQUEST] файл найден в истории анализа, анализ = " << analysis.dump() << std::endl;
        res.status = 200;
        res.set_content(analysis.dump(), "application/json");
    } else {
        std::cout << "[REQUEST] файл не найден в истории анализа" << std::endl;
        send_error(res, 500, "Internal server error");
    }
}

void FileAnalyseController::words_cloud_request(const httplib::Request& req, httplib::Response& res) {
    if (!is_valid_id(req)) {
        handle_empty_or_incorrect_id("id", res);
        return;
    }

    std::string document_id = extract_id_from_request(req);

    if (is_in_analysis_history(document_id)) {
        std::cout << "[REQUEST] файл найден в истории анализа" << std::endl;
        std::string words_cloud_url = get_words_cloud_url(document_id);
        if (words_cloud_url.empty()) {
            send_error(res, 404, "Words cloud URL not found");
            return;
        }
        std::cout << "[REQUEST] файл найден в истории анализа, url = " << words_cloud_url << std::endl;
        json response;
        response["words_cloud_url"] = words_cloud_url;

        res.status = 200;
        res.set_content(response.dump(), "application/json");
    } else {
        send_error(res, 404, "File not found in analysis history");
    }
}

bool FileAnalyseController::is_in_analysis_history(const std::string& id) {
    std::vector<std::string> params = {id};
    std::string query = "SELECT 1 FROM files_analysis.analyses_performed WHERE id = $1";

    pqxx::result response = db_.execute_query(query, params);

    return !response.empty();
}

nlohmann::json FileAnalyseController::get_file_analysis(const std::string& id) {
    std::cout << "[REQUEST] получаем анализ файла" << std::endl;
    std::vector<std::string> params = {id};
    std::string query = "SELECT * FROM files_analysis.analyses_performed WHERE id = $1";
    std::cout << "[REQUEST] запрос к БД: " << query << std::endl;
    pqxx::result response = db_.execute_query(query, params);
    std::cout << "[REQUEST] ответ от БД: " << response.size() << std::endl;
    nlohmann::json analysis_resp = nlohmann::json::array();
    if (response.empty()) {
        std::cout << "[REQUEST] файл не найден в истории анализа" << std::endl;
        return analysis_resp;
    }
    for (const auto& row : response) {
        nlohmann::json analysis;

        analysis["id"] = row["id"].as<std::string>();
        analysis["paragraphs_count"] = row["paragraphs_count"].as<std::string>();
        analysis["words_count"] = row["words_count"].as<std::string>();
        analysis["consonant_letters_count"] = row["consonant_letters_count"].as<std::string>();
        analysis["vowel_letters_count"] = row["vowel_letters_count"].as<std::string>();
        analysis["digits_count"] = row["digits_count"].as<std::string>();
        analysis["symbols_count"] = row["symbols_count"].as<std::string>();
        analysis["words_cloud_url"] = row["words_cloud_url"].as<std::string>();

        analysis_resp.push_back(analysis);
    }
    std::cout << "[REQUEST] анализ файла: " << analysis_resp.dump() << std::endl;
    return analysis_resp;
}

std::string FileAnalyseController::get_words_cloud_url(const std::string& id) {
    std::cout << "[REQUEST] получаем url облака слов" << std::endl;
    std::vector<std::string> params = {id};
    std::string query = "SELECT words_cloud_url FROM files_analysis.analyses_performed WHERE id = $1";
    std::cout << "[REQUEST] запрос к БД: " << query << std::endl;
    pqxx::result response = db_.execute_query(query, params);
    std::cout << "[REQUEST] ответ от БД: " << response.size() << std::endl;
    if (response.empty()) {
        return "";
    }
    std::cout << "[REQUEST] url облака слов: " << response[0][0].as<std::string>() << std::endl;
    return response[0][0].as<std::string>();
}