#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <utility>
#include "../../database/decorator/Decorator.h"
#include <spdlog/spdlog.h>

class Command {
public:
    virtual void Execute() = 0;

    virtual ~Command() = default;
};