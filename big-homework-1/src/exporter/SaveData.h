#include "../../database/decorator/Decorator.h"
#include "../../third_party/nlohmann/json.hpp"
#include <spdlog/spdlog.h>
#include <vector>
#include <unordered_map>
#include <optional>

class SaveData {
public:
    struct Payment {
        std::string operation_id;
        std::string operation_type;
        std::string bank_account_id;
        std::string category_id;
        std::string amount;
        std::string operation_date;
        std::optional<std::string> description;
    };

private:
    friend class FileSaver;

    static pqxx::result GetDataFromDB(const std::string& account_name, DatabaseFacade& db, const std::string& minutes) {
        std::string query;

        if (std::stoll(minutes) == 0) {
            query = "SELECT * FROM finance_tracker.operations WHERE account_name = $1";
        } else {
            query = "SELECT * FROM finance_tracker.operations WHERE account_name = $1 && operation_date > NOW() - INTERVAL '" + minutes + " minutes'";
        }

        std::vector<std::string> params = {account_name};

        pqxx::result response = db.ExecuteQuery(query, params);

        return response;
    }

    static std::vector<Payment> ConvertData(const pqxx::result& data) {
        std::vector<Payment> payments;
        for (const auto& row : data) {
            Payment payment;
            payment.operation_id = row["operation_id"].as<std::string>();
            payment.operation_type = row["operation_type"].as<std::string>();
            payment.bank_account_id = row["bank_account_id"].as<std::string>();
            payment.category_id = row["category_id"].as<std::string>();
            payment.amount = row["amount"].as<std::string>();
            payment.operation_date = row["operation_date"].as<std::string>();
            payment.description = row["description"].as<std::string>();
            payments.push_back(payment);
        }
        return payments;
    }
};

class FileSaver {
public:
    void Export(const std::string& filename, const std::string& account_name, const std::string& minutes, DatabaseFacade& db) {
       std::vector<SaveData::Payment> payments = SaveData::ConvertData(SaveData::GetDataFromDB(account_name, db, minutes));
       std::string formatted_data = FormatData(payments);

        std::ofstream file(filename);
        if (!file) {
            spdlog::error("Ошибка при открытии файла: {}", filename);
            return;
        }
        file << formatted_data;
        file.close();

        spdlog::info("Данные по банковскому счету : {} успешно сохранены в файл {}", account_name, filename);
    }

protected:
    // "= 0" говорит нам о том, что мы обязательно должны переопределить реализацию метода
    // во всех классах наследниках
    virtual std::string FormatData(const std::vector<SaveData::Payment>& payments) const = 0;
};

class CSVFileSaver : public FileSaver {
public:
    std::string FormatData(const std::vector<SaveData::Payment>& payments) const override {
        spdlog::info("Данные попали на форматирование в CSV формат.");
        std::stringstream ss;
        ss << "operation_id,operation_type,bank_account_id,category_id,amount,operation_date,description\n";
        for (const auto& payment : payments) {
            ss << payment.operation_id << ","
               << payment.operation_type << ","
               << payment.bank_account_id << ","
               << payment.category_id << ","
               << payment.amount << ","
               << payment.operation_date << ","
               << payment.description.value_or("") << "\n";
        }
        return ss.str();
    }
};

class YAMLFileSaver : public FileSaver {
public:
    std::string FormatData(const std::vector<SaveData::Payment>& payments) const override {
        spdlog::info("Данные попали на форматирование в YAML формат.");
        std::stringstream ss;
        ss << "payments:\n";
        for (const auto& payment : payments) {
            ss << "  - operation_id: " << payment.operation_id << "\n"
               << "    operation_type: " << payment.operation_type << "\n"
               << "    bank_account_id: " << payment.bank_account_id << "\n"
               << "    category_id: " << payment.category_id << "\n"
               << "    amount: " << payment.amount << "\n"
               << "    operation_date: " << payment.operation_date << "\n"
               << "    description: " << (payment.description ? *payment.description : "null") << "\n";
        }
        return ss.str();
    }
};

class JSONFileSaver : public FileSaver {
public:
    std::string FormatData(const std::vector<SaveData::Payment>& payments) const override {
        spdlog::info("Данные попали на форматирование в JSON формат.");
        nlohmann::json json_data;
        for (const auto& payment : payments) {
            json_data["payments"].push_back({
                    {"operation_id", payment.operation_id},
                    {"operation_type", payment.operation_type},
                    {"bank_account_id", payment.bank_account_id},
                    {"category_id", payment.category_id},
                    {"amount", payment.amount},
                    {"operation_date", payment.operation_date},
                    {"description", payment.description ? *payment.description : nullptr}
            });
        }
        return json_data.dump(4);
    }
};