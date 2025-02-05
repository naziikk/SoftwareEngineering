#include "../Animal/Animal.h"

class ZooVetClinic {
public:
    bool CheckHealth(Animal& animal) {
        return animal.IsHealthy();
    }
};