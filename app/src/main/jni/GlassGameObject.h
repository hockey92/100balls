#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"
#include "Line.h"
#include "CirclePhysicsObject.h"
#include "GlassPath.h"
#include "Shader.h"
#include "Drawable.h"
#include <list>

class GlassGameObject : public PhysicsObject, public Drawable {
public:
    GlassGameObject(GlassPath *glassPath);

    ~GlassGameObject();

    void update();

    void setChild(GlassGameObject *child);

    bool containsCircles();

    void clearCircles();

    void addCircle(CirclePhysicsObject *circlePhysicsObject);

    bool containsPoint(const Vec2 &point) const;

    virtual void updatePos();

    GlassGameObject *getTail();

    GlassGameObject *getHead();

    void doActionAfter();

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    Initializer *createInitializer();

private:
    GlassGameObject *parent;
    GlassGameObject *child;

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

    void setParent(GlassGameObject *parent);

    void innerUpdate();

    void updatePositionOnPath();

    void waste();
};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
