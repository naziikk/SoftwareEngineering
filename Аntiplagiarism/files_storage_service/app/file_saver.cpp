#include "file_saver.h"

std::string FileCreator::add_file_to_storage(const httplib::MultipartFormData& file) {
    long long hash = compute_hash(file);

    if (check_file_existence(hash)) {
        return get_file_id_by_hash(hash);
    }

    std::string filename = file.filename;
    save_file(filename, hash);

    std::string file_id = get_file_id_by_hash(hash);

    save_file(filename, file.content);

    return file_id;
}

std::string FileCreator::get_file_id_by_hash(long long hash) {
    std::vector<std::string> params = {std::to_string(hash)};
    pqxx::result response = db.execute_query("SELECT id FROM files_storage.files WHERE hash = $1", params);

    return response[0][0].as<std::string>();
}

bool FileCreator::check_file_existence(long long hash) {
    std::vector<std::string> params = {std::to_string(hash)};
    pqxx::result response = db.execute_query("SELECT id FROM files_storage.files WHERE hash = $1", params);

    return !response.empty();
}

void FileCreator::save_file(const std::string& file_name, const std::string& file_content, const std::string& file_id) {
    std::string location = "../infrastructure/files_storage/data/files/" + file_id + ".txt";

    std::ofstream out(location, std::ios::binary);
    out.write(file_content.c_str(), file_content.size());
    out.close();

    std::vector<std::string> params = {location, file_id};
    db.execute_query("UPDATE files_storage.files SET location = $1 WHERE id = $2", params);
}

void FileCreator::save_file(const std::string& file_name, long long hash) {
    std::vector<std::string> params = {file_name, std::to_string(hash)};
    db.execute_query("INSERT INTO files_storage.files (name, hash) VALUES ($1, $2)", params);
}

long long FileCreator::compute_hash(const httplib::MultipartFormData& file) {
    long long hash = 0;
    long long p_pow = 1;

    std::stringstream file_stream(file.content);
    std::string line;

    while (std::getline(file_stream, line)) {
        for (const auto& symbol : line) {
            hash = (hash + (symbol  + 1) * p_power) % MOD;
            p_pow = (p_pow * p) % MOD;
        }
    }

    return hash;
}