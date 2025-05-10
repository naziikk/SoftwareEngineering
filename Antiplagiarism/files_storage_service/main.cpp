#include "third_party/httplib.h"

#include "infrastructure/config/config.h"
#include "infrastructure/database/Database.h"

#include "app/file_saver.h"
#include "app/file_content_provider.h"

#include "controllers//file_crud_controller.h"

int main() {
    httplib::Server server;

    server.Options(".*", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:8009");
        res.set_header("Access-Control-Allow-Credentials", "true");
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

    db.init_db_from_file("infrastructure/database/files_storage.sql");
    pqxx::connection C(connection);
    pqxx::work W(C);

    FileCreator file_creating_service(db);
    FileContentProvider file_content_provider(db);
    FileCrudController file_crud_controller(file_creating_service, file_content_provider);

    server.Post("/file/upload", [&file_crud_controller, &set_cors_headers](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        file_crud_controller.add_file_to_storage_request(request, res);
    });

    server.Get("/file/:id", [&file_crud_controller, &set_cors_headers](const httplib::Request& request, httplib::Response &res) {
        set_cors_headers(res);
        file_crud_controller.get_file_by_id_request(request, res);
    });

    server.listen(cfg.server_.host, cfg.server_.port);
}