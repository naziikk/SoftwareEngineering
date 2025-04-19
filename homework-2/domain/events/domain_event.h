#pragma once
#include <iostream>

class DomainEvent {
public:
    virtual ~DomainEvent() = default;
    virtual std::string GetName() const = 0;
    virtual void Print() = 0;
};
