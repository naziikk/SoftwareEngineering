#include <iostream>
#include "../third_party/nlohmann/nlohmann.hpp"

#include "../app/file_saver.h"
#include "../app/file_content_provider.h"

#include "utils.h"

class FileCrudController {
public:
    FileCrudController(FileCreator& file_service, FileContentProdiver& file_provider) : file_service_(file_service), file_provider_(file_provider) {}

    static void add_file_to_storage_request(const httplib::Request& req, httplib::Response& res);

    static void get_file_by_id_request(const httplib::Request& req, httplib::Response& res);

private:
    using json = nlohmann::json;
    FileCreator& file_service_;
    FileContentProvider& file_provider_;
};

