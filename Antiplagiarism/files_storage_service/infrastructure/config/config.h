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
    std::string user;
    std::string password;
    int port;
};

struct Config {
    ServerCfg server_;
    DatabaseCfg database_;

    static Config MustLoadConfig(const std::string& path);
};