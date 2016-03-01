#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"
#include "Line.h"
#include "CirclePhysicsObject.h"
#include "GlassPath.h"
#include <list>

class GlassPhysicsObject : public PhysicsObject {
public:
    GlassPhysicsObject(GlassPath *glassPath);

    ~GlassPhysicsObject();

    void update();

    void setChildren(GlassPhysicsObject *children);

    bool containsCircles();

    void clear();

    void addCircle(CirclePhysicsObject *circlePhysicsObject);

    bool containsPoint(const Vec2 &point) const;

    GlassPhysicsObject *getTail();

    GlassPhysicsObject *getHead();

private:
    GlassPhysicsObject *parent;
    GlassPhysicsObject *child;

    float positionOnPath;
    float clearVel;
    bool isRotate;
    Line *lines[4];
    int numOfCircles;
    std::list<CirclePhysicsObject *> circles;

    GlassPath *glassPath;

    void setParent(GlassPhysicsObject *parent);

    void innerUpdate();
};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
