#include "GlassGameObject.h"
#include "GlassShape.h"
#include "Constants.h"

GlassGameObject::GlassGameObject(GlassPath *glassPath,
                                 RendererFactory *rendererFactory,
                                 Score *gameScore)
        : GameObject(new GlassShape(), 0.f),
          child(NULL),
          parent(NULL),
          isRotate(false),
          glassPath(glassPath),
          numOfCircles(0),
          wasted(false),
          numOfGlassesDistsBetweenThisAndParentGlasses(1),
          localScore(0),
          color(Color(1.0f, 1.0f, 1.0f, 1.0f)),
          gameScore(gameScore) {

    for (int i = 0; i < 3; i++) {
        lines[i] = new Line(((Segment *) getShape()->getChildren(i))->getPoint(0),
                            ((Segment *) getShape()->getChildren(i))->getPoint(1));
    }
    lines[3] = new Line(((Segment *) getShape()->getChildren(2))->getPoint(1),
                        ((Segment *) getShape()->getChildren(0))->getPoint(0));

    reset();

    int size = getShape()->verticesSize();
    float vertices[size];
    getShape()->getVertices(vertices);
    renderer = rendererFactory->createGeometryRenderer(vertices, size);
}

GlassGameObject::~GlassGameObject() {
    for (int i = 0; i < 4; i++) {
        delete lines[i];
    }
}

void GlassGameObject::update() {
    if (!parent && !wasted) {
        innerUpdate();
    }
}

void GlassGameObject::setChild(GlassGameObject *child) {
    this->child = child;
    child->setParent(this);
}

void GlassGameObject::setParent(GlassGameObject *parent) {
    this->parent = parent;
}

GlassGameObject *GlassGameObject::findNonRotateParent() {
    GlassGameObject *nonRotateParent = parent;
    while (nonRotateParent != NULL && nonRotateParent->isRotate) {
        nonRotateParent = nonRotateParent->parent;
    }
    return nonRotateParent;
}

void GlassGameObject::innerUpdate() {
    float currScoreVel = -0.5f;

    clearVel = currScoreVel;

    GlassGameObject *glassBefore = NULL;

    if (parent) {
        glassBefore = parent;
    } else {
        glassBefore = getTail();
        if (glassBefore == this) {
            glassBefore = NULL;
        }
    }

    if (glassBefore != NULL) {
        float parentPositionOnPath = glassBefore->positionOnPath;
        float distanceFromParent = glassPath->getDistanceBetweenPoints(parentPositionOnPath,
                                                                       positionOnPath);
        if (distanceFromParent < glassPath->getDistanceBetweenGlasses()) {
            float parentClearVel = glassBefore->clearVel;
            clearVel = parentClearVel -
                       0.01f * (distanceFromParent - glassPath->getDistanceBetweenGlasses()) / DT;
        }
    }

    float velDuringRotation = currScoreVel < -0.7f ? -0.7f : currScoreVel;

    float p1 = glassPath->getPointOnPath(6);
    float p2 = glassPath->getPointOnPath(7);
    float angleVel = (2.0f * PI) / (DT * ((p2 - p1) / (velDuringRotation * DT)));
    if (positionOnPath >= p1 && positionOnPath <= p2) {
        if (!isRotate) {
            setAngleVel(angleVel);
            isRotate = true;
        }
    } else {
        isRotate = false;
    }

    setVel((Vec2::cross(normal, 1) * clearVel) +
           (normal * (((len - glassPath->getDistFromPath()) * 0.1f) / DT)));

    if (isRotate) {
        setVel(Vec2(-velDuringRotation, 0.0f));
    }

    if (getShape()->getAngel() < -2.0f * PI) {
        getShape()->rotate(-getShape()->getAngel());
        setAngleVel(0.0f);
    }

    if (child) {
        child->innerUpdate();
    }
}

bool GlassGameObject::containsPoint(const Vec2 &point) const {
    Vec2 relPoint = point - getShape()->getCenter();
    for (int i = 0; i < 4; i++) {
        if (lines[i]->getValue(relPoint) < 0) {
            return false;
        }
    }
    return true;
}

bool GlassGameObject::containsCircles() {
    return !circles.empty();
}

void GlassGameObject::clearCircles() {
    circles.clear();
}

void GlassGameObject::addCircle(CircleGameObject *circlePhysicsObject) {
    circles.push_back(circlePhysicsObject);
    if (glassPath->isDown(normal)) {
        if (0 <= localScore && localScore < 50) {
            localScore += 1;
            gameScore->add(1);
        } else if (50 <= localScore && localScore < 100) {
            localScore += 2;
            gameScore->add(2);
        } else if (100 <= localScore) {
            localScore += 5;
            gameScore->add(5);
        }
        localScore++;
    }
    bool changeColor = true;
    if (0 <= localScore && localScore < 50) {
        changeColor = false;
        color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    } else if (50 <= localScore && localScore < 100) {
        color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    } else if (100 <= localScore && localScore < 150) {
        color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    } else if (150 <= localScore) {
        color = Color(1.0f, 0.0f, 1.0f, 1.0f);
    }
    if (changeColor) {
        for (std::list<CircleGameObject *>::iterator iter = circles.begin();
             iter != circles.end(); ++iter) {
            (*iter)->setColor(color);
        }
    }
}

GlassGameObject *GlassGameObject::getTail() {
    if (child != NULL) {
        return child->getTail();
    }
    return this;
}

GlassGameObject *GlassGameObject::getHead() {
    if (parent != NULL) {
        return parent->getHead();
    }
    return this;
}

void GlassGameObject::updatePos() {
    if (!isActive()) {
        return;
    }
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        if (getShape()->getCenter().y() < -2.0f) {
            setDeleted(true);
            return;
        }
        updatePositionOnPath();
    }
}

void GlassGameObject::updatePositionOnPath() {
    positionOnPath = glassPath->getPositionOnPath(getShape()->getCenter(), len, normal);
}

void GlassGameObject::doActionAfter(GlassGameObject **firstGlassPtr) {
    if (wasted) {
        return;
    }

    if (glassPath->isLeft(normal) && !containsCircles()) {
        waste(firstGlassPtr);
    } else if (glassPath->isRight(normal) && containsCircles()) {
        clearCircles();
    }
}

void GlassGameObject::waste(GlassGameObject **firstGlassPtr) {
    wasted = true;
    *firstGlassPtr = child;
    if (parent) {
        parent->child = child;
    }
    if (child) {
        child->parent = parent;
        child->numOfGlassesDistsBetweenThisAndParentGlasses += numOfGlassesDistsBetweenThisAndParentGlasses;
    }
    parent = NULL;
    child = NULL;
    setInvM(1);
}

void GlassGameObject::draw() {
    if (!isVisible() || isDeleted()) {
        return;
    }

    Vec2 center = getShape()->getCenter();
    renderer->setPosition(center.x(), center.y());
    renderer->setAngel(getShape()->getAngel());

    renderer->setColor(color.r(), color.g(), color.b(), 0.5f);
    renderer->setFilled(true);
    unsigned short vertices1[] = {0, 1, 2, 0, 2, 3};
    renderer->render(vertices1, 6);

    renderer->setFilled(false);
    renderer->setColor(color);
    unsigned short vertices2[] = {0, 1, 1, 2, 2, 3};
    renderer->render(vertices2, 6);
}

void GlassGameObject::reset() {
    child = NULL;
    parent = NULL;
    isRotate = false;
    numOfCircles = 0;
    wasted = false;
    numOfGlassesDistsBetweenThisAndParentGlasses = 1;
    localScore = 0;
    color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    BaseShape *shape = getShape();
    shape->setCenter(glassPath->getGlassStartPoint());
    shape->rotate(shape->getAngel());
    setDeleted(false);
    updatePositionOnPath();
    setInvM(0);
}
