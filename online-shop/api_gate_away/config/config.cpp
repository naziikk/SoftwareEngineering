#include "config.h"

Config Config::MustLoadConfig(const std::string& path) {
    Config config;
    try {
        YAML::Node root = YAML::LoadFile(path);

        auto server = root["server"];
        config.server_.host = server["host"].as<std::string>();
        config.server_.port = server["port"].as<int>();
    } catch (...) {
        std::cerr << "Failed to load config" << std::endl;
        throw;
    }
    return config;
}