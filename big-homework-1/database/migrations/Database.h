#pragma once
#include <pqxx/pqxx>
#include <iostream>
#include <fstream>

class Database {
    pqxx::connection conn_;

public:
    Database() {};

    Database(const std::string& con);

    void initDbFromFile(const std::string& filename);

    pqxx::result executeQueryWithParams(const std::string& query, std::vector<std::string>& params) {
        try {
            pqxx::work txn(conn_);
            pqxx::result res = txn.exec_params(pqxx::zview(query), pqxx::prepare::make_dynamic_params(params));
            txn.commit();
            return res;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
            pqxx::result empty_result;
            return empty_result;
        }
    }
};