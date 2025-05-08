#include "../third_party/httplib.h"
#include "../infrastructure/database/Database.h"

class Analyzer {
public:
    Analyzer(Database& db) : db_(db) {}

    void analyse_file(const httplib::MultipartFormData& file, const std::string& file_id);

    void generate_words_cloud(const std::string& file_content, Analysis& analysis);

private:
    struct Analysis {
        std::string id;
        std::string words_cloud_location;
        long long paragraphs_count;
        long long words_count;
        long long consonant_letters_count;
        long long vowel_letters_count;
        long long digits_count;
        long long symbols_count;
    };
    Database& db_;

private:
    Analysis get_analysis(const httplib::MultipartFormData& file, const std::string& file_id);

    void save_analysis(const Analysis& analysis);
};

