#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"
#include "Line.h"
#include "CircleGameObject.h"
#include "GlassPath.h"
#include "Shader.h"
#include "Drawable.h"
#include "GameObject.h"
#include <list>

class GlassGameObject : public GameObject {
public:
    GlassGameObject(GlassPath *glassPath);

    ~GlassGameObject();

    void update();

    void setChild(GlassGameObject *child);

    bool containsCircles();

    void clearCircles();

    void addCircle(CircleGameObject *circlePhysicsObject);

    bool containsPoint(const Vec2 &point) const;

    virtual void updatePos();

    GlassGameObject *getTail();

    GlassGameObject *getHead();

    void doActionAfter();

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    void reset();

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
    std::list<CircleGameObject *> circles;
    float initVelValue;
    bool wasted;
    int numOfGlassesToParent;
    int score;
    Color color;
    GlassPath *glassPath;

    void setParent(GlassGameObject *parent);

    void innerUpdate();

    void updatePositionOnPath();

    void waste();
};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
