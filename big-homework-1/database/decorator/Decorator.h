#pragma once
#include <pqxx/pqxx>
#include <iostream>
#include <fstream>

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual pqxx::result ExecuteQuery(const std::string& query, const std::vector<std::string>& params) = 0;
};

class DatabaseDecorator : public IDatabase {
protected:
    std::shared_ptr<IDatabase> db_;

public:
    explicit DatabaseDecorator(std::shared_ptr<IDatabase> db) : db_(std::move(db)) {}

    pqxx::result ExecuteQuery(const std::string& query, const std::vector<std::string>& params) override {
        return db_->ExecuteQuery(query, params);
    }
};