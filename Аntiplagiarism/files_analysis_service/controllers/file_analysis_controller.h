#include <iostream>
#include "utils.h"

class FileAnalyseController {
public:
    void file_analysis_request(const httplib:Request& res, httplib::Response& res);

    void words_cloud_request(const httplib:Request& res, httplib::Response& res);

private:
    using json = nlohmann::json;
};

