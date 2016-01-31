#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"

class GlassPhysicsObject : public PhysicsObject {
public:
    GlassPhysicsObject();
    void update();

private:
    Segment*path[4];

};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
