#include <iostream>
#include "../infrastructure/database/Database.h"
#include "../app/analyzer.h"
#include "utils.h"

class FileAnalyseController {
public:
    FileAnalyseController(Database& db, Analyzer& analyzer) : db_(db), analyzer_(analyzer) {}

    void file_analysis_request(const httplib::Request& req, httplib::Response& res);

    void words_cloud_request(const httplib::Request& req, httplib::Response& res);

private:
    bool is_in_analysis_history(const std::string& id);

    nlohmann::json get_file_analysis(const std::string& id);

    std::string get_words_cloud_location(const std::string& id);

private:
    using json = nlohmann::json;

    Database& db_;
    Analyzer& analyzer_;
};

