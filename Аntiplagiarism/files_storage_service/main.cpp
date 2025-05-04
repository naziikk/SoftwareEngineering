#include "third_party/httplib.h"

#include "infrastructure/config/config.h"

#include "app/file_saver.h"
#include "app/file_content_provider.h"

#include "presentation/file_crud_controller.h"

int main() {
    Config cfg = Config::MustLoadConfig("/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/Аntiplagiarism/files_storage_service/infrastructure/config/config.yaml");
    httplib::Server server;
    std::string connection = "dbname=" + cfg.database_.db_name + " host=" + cfg.database_.host + " port=" + std::to_string(cfg.database_.port);
    Database db(connection);

    db.initDbFromFile("infrastructure/database/files_storage.sql");
    pqxx::connection C(connect);
    pqxx::work W(C);
    W.commit();

    FileCreator file_creating_service(db);
    FileContentProvider file_content_provider(db);
    FileCrudController file_crud_controller(file_creating_service, file_content_provider);

    try {
        server.Post("/file/upload", [](const httplib::Request& request, httplib::Response &res) {
            FileCrudController::add_file_to_storage_request(request, res);
        });

        server.Get("/file/:id", [](const httplib::Request& request, httplib::Response &res) {
            FileCrudController::get_file_by_id_request(request, res);
        });

    } catch (...) {
        std::cerr << "Some shit happens" << '\n';
        return 1;
    }

    server.listen(cfg.server_.host, cfg.server_.port);

    return 0;
}