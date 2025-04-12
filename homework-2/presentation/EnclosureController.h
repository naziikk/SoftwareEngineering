#pragma once
#include "../infrastructure/third_party/httplib.h"
#include <iostream>

class EnclosureController {
public:
    static void AddEnclosure(const httplib::Request& request, httplib::Response &res);

    static void RemoveEnclosure(const httplib::Request& request, httplib::Response &res);
};
