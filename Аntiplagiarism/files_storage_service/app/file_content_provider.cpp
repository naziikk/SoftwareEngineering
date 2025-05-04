#include "file_content_provider.h"

std::pair<int, std::stringstream> FileContentProvider::get_file_content(const std::string& file_id) {
    if (!check_file_existence(file_id)) {
        return {404, std::stringstream()};
    }

    std::string file_location = get_file_location(file_id);
    std::stringstream file_stream = get_file_stream(file_location);

    if (file_stream.str().empty()) {
        return {500, std::stringstream()};
    }

    return {200, file_stream};
}

bool FileContentProvider::check_file_existence(const std::string& file_id) {
    std::vector<std::string> params = {file_id};
    pqxx::result response = db.execute_query("SELECT * FROM files_storage.files WHERE id = $1", params);

    return !response.empty();
}

std::string FileContentProvider::get_file_location(const std::string& file_id) {
    std::vector<std::string> params = {file_id};
    pqxx::result response = db.execute_query("SELECT location FROM files_storage.files WHERE id = $1", params);

    return response[0][0].as<std::string>();
}

std::stringstream FileContentProvider::get_file_stream(const std::string& file_location) {
    std::ifstream file(file_location, std::ios::binary);
    if (!file || !file.is_open()) {
        throw std::runtime_error("НАДО ДЕБАЖИТЬ ЙОУ");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer;
}