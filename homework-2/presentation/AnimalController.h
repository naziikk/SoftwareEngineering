#pragma once
#include "../infrastructure/third_party/httplib.h"
#include <iostream>

class AnimalController {
public:
    static void AddAnimal(const httplib::Request& request, httplib::Response &res);

    static void RemoveAnimal(const httplib::Request& request, httplib::Response &res);

    static void MoveAnimal(const httplib::Request& request, httplib::Response &res);
};

