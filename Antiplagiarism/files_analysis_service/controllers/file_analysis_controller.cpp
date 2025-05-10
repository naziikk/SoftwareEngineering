#include "file_analysis_controller.h"

void FileAnalyseController::file_analysis_request(const httplib::Request& req, httplib::Response& res) {
    if (!is_valid_id(req)) {
        handle_empty_or_incorrect_id("id", res);
        return;
    }

    std::string document_id = extract_id_from_request(req);
    if (is_in_analysis_history(document_id)) {
        json analysis = get_file_analysis(document_id);

        res.status = 200;
        res.set_content(analysis.dump(), "application/json");

        return;
    }

    const auto& file = req.files.begin()->second;

    analyzer_.analyse_file(file, document_id);

    if (is_in_analysis_history(document_id)) {
        json analysis = get_file_analysis(document_id);

        res.status = 200;
        res.set_content(analysis.dump(), "application/json");
    } else {
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
        std::string words_cloud_url = get_words_cloud_url(document_id);
        if (words_cloud_url.empty()) {
            send_error(res, 404, "Words cloud URL not found");
            return;
        }

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
    std::vector<std::string> params = {id};
    std::string query = "SELECT * FROM files_analysis.analyses_performed WHERE id = $1";

    pqxx::result response = db_.execute_query(query, params);

    nlohmann::json analysis_resp = nlohmann::json::array();
    if (response.empty()) {
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

    return analysis_resp;
}

std::string FileAnalyseController::get_words_cloud_url(const std::string& id) {
    std::vector<std::string> params = {id};
    std::string query = "SELECT words_cloud_url FROM files_analysis.analyses_performed WHERE id = $1";

    pqxx::result response = db_.execute_query(query, params);

    if (response.empty()) {
        return "";
    }

    return response[0][0].as<std::string>();
}