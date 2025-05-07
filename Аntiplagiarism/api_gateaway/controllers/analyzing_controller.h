#include <iostream>
#include "../utils.h"
#include "../third_party/httplib.h"
#include "../third_party/nlohmann/json.hpp"

void get_analysis(const httplib::Request& req, httplib::Response& res) {

}

void get_words_cloud(const httplib::Request& req, httplib::Response& res) {
    std::string document_id = extract_id_from_request(req);
    httplib::Client storage("http::localhost:8008");
    storage.set_connection_timeout(10);
    storage.set_read_timeout(10);
    storage.set_default_headers({
            {"Content-Type", "application/json"},
            {"Accept", "application/json"}
    });

    auto response_from_storage = storage->Get("/words_cloud/" + document_id);

    if (response && res->status = 200) {

    } else if (res->status == 404) {
        send_error(res, 404, "File with id: " + document_id + " not found");
    } else {
        send_error(res, 500, "Shit happens");
    }
}