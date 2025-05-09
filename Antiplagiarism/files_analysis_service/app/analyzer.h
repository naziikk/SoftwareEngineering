#pragma once

#include "../controllers/utils.h"

#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

#include "../infrastructure/database/Database.h"

class Analyzer {
public:
    Analyzer(Database& db) : db_(db) {}

    void analyse_file(const httplib::MultipartFormData& file, const std::string& file_id);

private:
    struct Analysis {
        std::string id;
        std::string words_cloud_url;
        long long paragraphs_count = 0;
        long long words_count = 0;
        long long consonant_letters_count = 0;
        long long vowel_letters_count = 0;
        long long digits_count = 0;
        long long symbols_count = 0;
    };
    Database& db_;

private:
    Analysis get_analysis(const httplib::MultipartFormData& file, const std::string& file_id);

    void save_analysis(const Analysis& analysis);

    void generate_words_cloud(const std::string& file_content, Analysis& analysis);

private:
    using json = nlohmann::json;
};

