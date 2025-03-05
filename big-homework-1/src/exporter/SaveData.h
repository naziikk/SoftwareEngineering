#include "../../database/migrations/Database.h"
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
        long long amount;
        std::string operation_date;
        std::optional<std::string> description;
    };

private:
    friend class FileSaver;

    static pqxx::result GetDataFromDB(const std::string& bank_account_id, DatabaseFacade& db) {
        std::string query = "SELECT * FROM finance_tracker.operations WHERE bank_account_id = $1";
        std::vector<std::string> params = {bank_account_id};

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
            payment.amount = row["amount"].as<long long>();
            payment.operation_date = row["operation_date"].as<std::string>();
            payment.description = row["description"].as<std::string>();
            payments.push_back(payment);
        }
        return payments;
    }
};

class FileSaver {
public:
    void Export(const std::string& filename, const std::string& bank_account_id, DatabaseFacade& db) {
       std::vector<SaveData::Payment> payments = SaveData::ConvertData(SaveData::GetDataFromDB(bank_account_id, db));

        spdlog::info("Данные по банковскому счету с id: {} успешно сохранены в файл.", bank_account_id);
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
    }
};

class YAMLFileSaver : public FileSaver {
public:
    std::string FormatData(const std::vector<SaveData::Payment>& payments) const override {
        spdlog::info("Данные попали на форматирование в YAML формат.");
    }
};

class JSONFileSaver : public FileSaver {
public:
    std::string FormatData(const std::vector<SaveData::Payment>& payments) const override {
        spdlog::info("Данные попали на форматирование в JSON формат.");
    }
};