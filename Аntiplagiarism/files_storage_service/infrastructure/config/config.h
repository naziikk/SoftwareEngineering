#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>

struct ServerCfg {
    std::string host;
    int port;
};

struct DatabaseCfg {
    std::string db_name;
    std::string host;
    int port;
};

struct Config {
    ServerCfg server_;
    DatabaseCfg database_;

    static Config MustLoadConfig(const std::string& path);
};