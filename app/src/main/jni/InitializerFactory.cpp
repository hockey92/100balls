#include <stddef.h>
#include "InitializerFactory.h"
#include "ShapeTypesEnum.h"
#include "GlassInitializer.h"

Initializer * InitializerFactory::createInitializer(unsigned int type) {

    switch (type) {
        case 10:
            return new GlassInitializer();
        default:
            return NULL;
    }
}
