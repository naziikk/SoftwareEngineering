#pragma once
#include <iostream>
#include <spdlog/spdlog.h>

class Observer {
public:
    virtual void Update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

class Logger : public Observer {
public:
    void Update(const std::string& message) override {
        spdlog::info(message);
    }
};