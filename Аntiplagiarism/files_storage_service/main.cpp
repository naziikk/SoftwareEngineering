#include "third_party/httplib.h"

#include "infrastructure/config/config.h"
#include "infrastructure/database/Database.h"

#include "app/file_saver.h"
#include "app/file_content_provider.h"

#include "controllers//file_crud_controller.h"

int main() {
    Config cfg = Config::MustLoadConfig("../infrastructure/config/config.yaml");
    httplib::Server server;
    std::string connection = "dbname=" + cfg.database_.db_name + " host=" + cfg.database_.host + " port=" + std::to_string(cfg.database_.port);
    Database db(connection);

    db.init_db_from_file("/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/Аntiplagiarism/files_storage_service/infrastructure/database/files_storage.sql");
    pqxx::connection C(connection);
    pqxx::work W(C);

    FileCreator file_creating_service(db);
    FileContentProvider file_content_provider(db);
    FileCrudController file_crud_controller(file_creating_service, file_content_provider);

    server.Post("/file/upload", [&](const httplib::Request& request, httplib::Response &res) {
        file_crud_controller.add_file_to_storage_request(request, res);
    });

    server.Get("/file/:id", [&](const httplib::Request& request, httplib::Response &res) {
        file_crud_controller.get_file_by_id_request(request, res);
    });

    server.listen(cfg.server_.host, cfg.server_.port);
}