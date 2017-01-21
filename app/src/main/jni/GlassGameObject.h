#ifndef NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Segment.h"
#include "Line.h"
#include "CircleGameObject.h"
#include "GlassPath.h"
#include "Shader.h"
#include "GameObject.h"
#include "RendererFactory.h"
#include "GLGeometryRenderer.h"
#include "Score.h"
#include <list>

class GlassGameObject : public GameObject {
public:
    GlassGameObject(GlassPath *glassPath, RendererFactory *rendererFactory, Score *gameScore);

    virtual ~GlassGameObject();

    void update(float dt);

    void setChild(GlassGameObject *child);

    bool containsCircles();

    void clearCircles();

    void addCircle(CircleGameObject *circlePhysicsObject);

    bool containsPoint(const Vec2 &point) const;

    virtual void updatePos(float dt);

    GlassGameObject *getTail();

    GlassGameObject *getHead();

    void doActionAfter(GlassGameObject **firstGlassPtr);

    void draw(float delta);

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
    bool wasted;
    int numOfGlassesDistsBetweenThisAndParentGlasses;
    int localScore;
    Color color;
    GlassPath *glassPath;

    Score* gameScore;

    GeometryRenderer *renderer;

    void setParent(GlassGameObject *parent);

    void innerUpdate(float dt);

    void updatePositionOnPath();

    void waste(GlassGameObject **firstGlassPtr);

    GlassGameObject *findNonRotateParent();
};

#endif //NATIVE_ACTIVITY_GLASSPHYSICSOBJECT_H
