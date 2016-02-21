#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"

class GlassPhysicsObject : public PhysicsObject {
public:
    GlassPhysicsObject();

    void update();

    void setChildren(GlassPhysicsObject *children);

private:
    Segment *path[4];
    GlassPhysicsObject *parent;
    GlassPhysicsObject *children;
    float right;
    float left;
    float down;
    float up;
    float pathLen;
    float distFromPath;
    float positionOnPath;
    float clearVel;

    void setParent(GlassPhysicsObject *parent);

    void innerUpdate();

    float getPositionOnPath(Vec2 normal, Vec2 point);

    bool isZero(float value);
};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
