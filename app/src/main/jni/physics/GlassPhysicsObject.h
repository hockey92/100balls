#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"
#include "Line.h"
#include "CirclePhysicsObject.h"
#include "GlassPath.h"
#include "Shader.h"
#include <list>

class GlassPhysicsObject : public PhysicsObject {
public:
    GlassPhysicsObject(GlassPath *glassPath);

    ~GlassPhysicsObject();

    void update();

    void setChild(GlassPhysicsObject *child);

    bool containsCircles();

    void clearCircles();

    void addCircle(CirclePhysicsObject *circlePhysicsObject);

    bool containsPoint(const Vec2 &point) const;

    virtual void updatePos();

    GlassPhysicsObject *getTail();

    GlassPhysicsObject *getHead();

    void doActionAfter();

private:
    GlassPhysicsObject *parent;
    GlassPhysicsObject *child;

    float positionOnPath;
    float len;

    Vec2 normal;
    float clearVel;
    bool isRotate;
    Line *lines[4];
    int numOfCircles;
    std::list<CirclePhysicsObject *> circles;
    float initVelValue;
    bool wasted;
    int numOfGlassesToParent;
    int score;

    GlassPath *glassPath;

    void setParent(GlassPhysicsObject *parent);

    void innerUpdate();

    void updatePositionOnPath();

    void waste();

    void draw(float *projMat, Shader *simpleShader);
};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
