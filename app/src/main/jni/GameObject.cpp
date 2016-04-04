#include "GameObject.h"
#include "SimpleInitializer.h"

Initializer *GameObject::createInitializer() {
    return new SimpleInitializer(getShape());
}
