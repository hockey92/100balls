#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"
#include "Line.h"
#include "CirclePhysicsObject.h"
#include <list>

class GlassPhysicsObject : public PhysicsObject {
public:
    GlassPhysicsObject();

    ~GlassPhysicsObject();

    void update();

    void setChildren(GlassPhysicsObject *children);

    bool containsCircles();

    void clear();

    void addCircle(CirclePhysicsObject *circlePhysicsObject);

    bool containsPoint(const Vec2 &point) const;

    static float getDistanceBetweenGlasses(GlassPhysicsObject *glass1,
                                           GlassPhysicsObject *glass);

    GlassPhysicsObject *getTail();

    GlassPhysicsObject *getHead();

private:
    Segment *path[4];
    GlassPhysicsObject *parent;
    GlassPhysicsObject *child;
    float right;
    float left;
    float down;
    float up;
    float pathLen;
    float distFromPath;
    float positionOnPath;
    float clearVel;
    float quartOfCircleLen;
    bool isRotate;
    Line *lines[4];
    int numOfCircles;
    std::list<CirclePhysicsObject *> circles;

    void setParent(GlassPhysicsObject *parent);

    void innerUpdate();

    float getPositionOnPath(const Vec2 &center, float &len, Vec2 &normal);

    bool isZero(float value);
};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
