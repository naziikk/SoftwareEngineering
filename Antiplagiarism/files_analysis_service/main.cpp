#include "third_party/httplib.h"
#include "infrastructure/database/Database.h"
#include "infrastructure/config/config.h"

#include "app/analyzer.h"

#include "controllers/file_analysis_controller.h"

int main() {
    httplib::Server server;

    server.Options(".*", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Origin", "http://localhost:8009");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        res.status = 200;
    });

    auto set_cors_headers = [&](httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:8009");
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    };

    Config cfg = Config::MustLoadConfig("infrastructure/config/config.yaml");
    std::string connection = "dbname=" + cfg.database_.db_name + " host=" + cfg.database_.host + " port=" + std::to_string(cfg.database_.port) +
                              " user=" + cfg.database_.user + " password=" + cfg.database_.password;
    Database db(connection);
    db.init_db_from_file("infrastructure/database/files_analysis.sql");
    pqxx::connection C(connection);
    pqxx::work W(C);
    W.commit();
    Analyzer analyzer(db);
    FileAnalyseController file_analyze_controller(db, analyzer);

    server.Post("/file/:id/analysis", [&file_analyze_controller, &set_cors_headers](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        file_analyze_controller.file_analysis_request(request, res);
    });

    server.Get("/file/:id/words_cloud", [&file_analyze_controller, &set_cors_headers](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        file_analyze_controller.words_cloud_request(request, res);
    });

    std::cout << "Server is running on " << cfg.server_.host << ":" << cfg.server_.port << std::endl;
    server.listen(cfg.server_.host, cfg.server_.port);
}