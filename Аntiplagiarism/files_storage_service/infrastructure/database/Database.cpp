#include "Database.h"

Database::Database(const std::string& con) : conn_(con) { }

void Database::init_db_from_file(const std::string &filename) {
    std::lock_guard<std::mutex> lock(conn_mutex_); 
    
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sql = buffer.str();

    try {
        pqxx::work txn(conn_);
        txn.exec(sql);
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

pqxx::result Database::execute_query(const std::string& query, std::vector<std::string>& params) {
    std::lock_guard<std::mutex> lock(conn_mutex_);

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