#include "third_party/httplib.h"
#include "infrastructure/database/Database.h"
#include "infrastructure/config/config.h"

#include "app/analyzer.h"

#include "controllers/file_analysis_controller.h"

int main() {
    Config cfg = Config::MustLoadConfig("/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/Аntiplagiarism/files_analysis_service/infrastructure/config/config.yaml");
    httplib::Server server;
    std::string connection = "dbname=" + cfg.database_.db_name + " host=" + cfg.database_.host + " port=" + std::to_string(cfg.database_.port);
    Database db(connection);

    db.init_db_from_file("infrastructure/database/files_storage.sql");
    pqxx::connection C(connection);
    pqxx::work W(C);
    W.commit();

    Analyzer& analyzer(db);
    FileAnalyseController file_analyze_controller(db, analyzer);

    try {
        server.Post("/file/:id/analysis", [&](const httplib::Request& request, httplib::Response &res) {
            file_analyze_controller.file_analysis_request(request, res);
        });

        server.Get("/file/:id/words_cloud", [&](const httplib::Request& request, httplib::Response &res) {

        });

    } catch (...) {
        std::cerr << "Some shit happens" << '\n';
        return 1;
    }

    server.listen(cfg.server_.host, cfg.server_.port);
    return 0;
}