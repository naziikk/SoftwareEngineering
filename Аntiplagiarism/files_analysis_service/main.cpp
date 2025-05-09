#include "third_party/httplib.h"
#include "infrastructure/database/Database.h"
#include "infrastructure/config/config.h"

#include "app/analyzer.h"

#include "controllers/file_analysis_controller.h"

int main() {
    Config cfg = Config::MustLoadConfig("../infrastructure/config/config.yaml");
    std::string connection = "dbname=" + cfg.database_.db_name + " host=" + cfg.database_.host + " port=" + std::to_string(cfg.database_.port);
    Database db(connection);
    db.init_db_from_file("/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/Аntiplagiarism/files_analysis_service/infrastructure/database/files_analysis.sql");
    pqxx::connection C(connection);
    pqxx::work W(C);
    W.commit();
    Analyzer analyzer(db);
    FileAnalyseController file_analyze_controller(db, analyzer);

    httplib::Server server;

    server.Post("/file/:id/analysis", [&file_analyze_controller](const httplib::Request& request, httplib::Response &res) {
        file_analyze_controller.file_analysis_request(request, res);
    });

    server.Get("/file/:id/words_cloud", [&file_analyze_controller](const httplib::Request& request, httplib::Response &res) {
        std::cout << "Received request for words cloud" << std::endl;
        file_analyze_controller.words_cloud_request(request, res);
    });

    std::cout << "Server is running on " << cfg.server_.host << ":" << cfg.server_.port << std::endl;
    server.listen(cfg.server_.host, cfg.server_.port);
}