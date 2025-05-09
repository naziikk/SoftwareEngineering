#include "file_crud_controller.h"

void FileCrudController::add_file_to_storage_request(const httplib::Request& req, httplib::Response& res) {
    const auto& file = req.files.begin()->second;
    std::string file_id = file_service_.add_file_to_storage(file);

    if (file_id.empty()) {
        send_error(res, 500, "Failed to add file to storage");
        return;
    }

    json response_json;
    response_json["id"] = file_id;
    res.set_content(response_json.dump(), "application/json");
    res.status = 200;
}

void FileCrudController::get_file_by_id_request(const httplib::Request& req, httplib::Response& res) {
    std::string document_id = extract_id_from_request(req);

    if (document_id.empty()) {
        handle_empty_field("id", res);
        return;
    }

    try {
        auto [status_code, file_stream] = file_provider_.get_file_content(document_id);

        if (status_code != 200) {
            send_error(res, status_code, "Failed to get file content");
            return;
        }

        res.set_content(file_stream->str(), "text/plain");
        res.set_header("Content-Disposition", "attachment; filename=\"" + document_id + ".txt\"");
        res.status = 200;
    } catch (...) {
        std::cerr << "Error while getting file content" << std::endl;
        return;
    }
}