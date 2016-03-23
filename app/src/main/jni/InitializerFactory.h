#ifndef NATIVE_ACTIVITY_INITIALIZERFACTORY_H
#define NATIVE_ACTIVITY_INITIALIZERFACTORY_H

#include "Initializer.h"

class InitializerFactory {
public:
    static Initializer * createInitializer(unsigned int type);
};

#endif //NATIVE_ACTIVITY_INITIALIZERFACTORY_H
