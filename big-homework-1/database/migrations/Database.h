#pragma once
#include <pqxx/pqxx>
#include <iostream>
#include <fstream>

class DatabaseFacade {
    pqxx::connection conn_;

public:
    DatabaseFacade() {};

    DatabaseFacade(const std::string& con) : conn_(con) {}

    void Init(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удается открыть файл");
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string sql = buffer.str();

        try {
            pqxx::work txn(conn_);
            txn.exec(sql);
            txn.commit();
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << '\n';
        }
    }

    pqxx::result ExecuteQuery(const std::string& query, std::vector<std::string>& params) {
        try {
            // начинаем транзакцию, выполняем непосредственно транзакцию и делаем коммит
            // потому что если вдруг что-то случится во время запроса, транзакция откатится
            // и бд останется в согласованном состоянии
            pqxx::work txn(conn_);
            pqxx::result res = txn.exec_params(pqxx::zview(query), pqxx::prepare::make_dynamic_params(params));
            txn.commit();
            return res;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << '\n';
            pqxx::result empty_result;
            return empty_result;
        }
    }
};