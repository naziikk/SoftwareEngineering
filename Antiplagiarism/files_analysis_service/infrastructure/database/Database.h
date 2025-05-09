#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>

class Database {
private:
    pqxx::connection conn_;
    std::mutex mtx;

public:
    Database() {};

    Database(const std::string& con);

    void init_db_from_file(const std::string& filename);

    pqxx::result execute_query(const std::string& query, std::vector<std::string>& params);
};