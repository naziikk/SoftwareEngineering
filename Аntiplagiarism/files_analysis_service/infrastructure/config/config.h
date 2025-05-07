#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>

struct ServerCfg {
    std::string host;
    int port;
};

struct Config {
    ServerCfg server_;

    static Config MustLoadConfig(const std::string& path);
};