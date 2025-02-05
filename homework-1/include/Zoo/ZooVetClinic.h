#pragma once
#include "../Animal/Animal.h"

class ZooVetClinic {
public:
    bool CheckHealth(Animal& animal) {
        return animal.IsHealthy();
    }

    void TreatAnimal(Animal& animal) {
        animal.Treat();
    }
};