#pragma once

#include <iostream>
#include <fstream>
#include "../infrastructure/database/Database.h"
#include "../infrastructure/database/Database.h"
#include "../third_party/httplib.h"

class FileCreator {
public:
    explicit FileCreator(Database& db) : db(db) {}

    std::string add_file_to_storage(const httplib::MultipartFormData& file);

    std::string get_file_id_by_hash(long long file_id);

private:
    bool check_file_existence(long long hash);

    void save_file(const std::string& file_name, const std::string& file_content, const std::string& file_id);

    long long compute_hash(const httplib::MultipartFormData& file);

    void save_file(const std::string& file_name, long long hash);

private:
    const int MOD = 1e9 + 7;
    const int p = 31;

    Database& db;
};

