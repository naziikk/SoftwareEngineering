#pragma once

#include <iostream>
#include <fstream>
#include "../infrastructure/database/Database.h"
#include "../infrastructure/database/Database.h"


class FileContentProvider {
public:
    FileContentProvider(Database& db) : db(db) {}

    std::pair<int, std::unique_ptr<std::stringstream>> get_file_content(const std::string& file_id);

private:
    bool check_file_existence(const std::string& file_id);

    std::string get_file_location(const std::string& file_id);

    std::stringstream get_file_stream(const std::string& file_location);
private:
    Database& db;
};


