#include "PhysicsService.h"
#include "Container.h"
#include "Gate.h"
#include "common.hpp"
#include "GameCoords.h"

PhysicsService::PhysicsService() {

    float distanceBetweenCircles = 0.005f;
    float r = GameCoords::getInstance()->getCoords(CIRCLE)->getData()[0];

    addCircles(GameCoords::getInstance()->getCoords(CONTAINER)->getData()[4] + r +
               distanceBetweenCircles,
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[5] - r -
               distanceBetweenCircles, 1.0f, r, distanceBetweenCircles, false, 30);

    addCircles(GameCoords::getInstance()->getCoords(CONTAINER)->getData()[22] - r -
               distanceBetweenCircles,
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[23] - r -
               distanceBetweenCircles, -1.0f, r, distanceBetweenCircles, false, 30);

    addCircles(-2.0f * (2.0f * r + distanceBetweenCircles),
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[23] - r -
               distanceBetweenCircles, 1.0f, r, distanceBetweenCircles, true, 40);

    container = new PhysicsObject(new Container(), 0.f);
    physicsObjects.push_back(container);

    for (int i = 0; i < 7; i++) {
        GlassPhysicsObject *po = new GlassPhysicsObject(&glassPath);
        physicsObjects.push_back(po);
        glasses.push_back(po);
        if (i == 0) {
            firstGlass = po;
        } else {
            po->setActive(false);
            po->setVisible(false);
            frozenGlasses.push(po);
        }
    }

    gate = new PhysicsObject(new Gate(), 0.f);
    physicsObjects.push_back(gate);
}

void PhysicsService::addCircles(float initX, float initY, float direction, float r,
                                float distanceBetweenCircles, bool active, int numOfCircles) {
    for (int i = 0; i < numOfCircles; i++) {
        float x = initX + direction * (i % 5) * (2.0f * r + distanceBetweenCircles);
        float y = initY - (i / 5) * (2.0f * r + distanceBetweenCircles);
        CirclePhysicsObject *po = new CirclePhysicsObject(r, 1.0f);
        if (!active) {
            frozenCircles.push(po);
        }
        po->setActive(active);
        po->getShape()->move(Vec2(x, y));
        physicsObjects.push_back(po);
        circles.push_back(po);
    }
}

void PhysicsService::open() {
    gate->setActive(false);
}

void PhysicsService::close() {
    gate->setActive(true);
}

void PhysicsService::doActionBefore() {

}

void PhysicsService::doActionAfter() {

    for (int i = 0; i < glasses.size(); i++) {
        GlassPhysicsObject *glass = glasses[i];
        if (!glass->isActive()) {
            continue;
        }
        glass->doActionAfter();
    }

    checkFrozenGlasses();

    int MAX_NUM_OF_ACTIVE_CIRCLES = 40;
    int realNumOfActiveCircles = 0;
    for (int i = 0; i < circles.size(); i++) {
        CirclePhysicsObject *circle = circles[i];
        if (circle->isActive()) {
            realNumOfActiveCircles++;
            bool insideGlass = false;
            for (int j = 0; j < glasses.size(); j++) {
                GlassPhysicsObject *glass = glasses[j];
                if (glass->isActive() && glass->containsPoint(circle->getShape()->getCenter())) {
                    insideGlass = true;
                    if (!circle->isInsideGlass()) {
                        glass->addCircle(circle);
                    }
                }
            }
            circle->setInsideGlass(insideGlass);
        }
    }
    if (realNumOfActiveCircles < MAX_NUM_OF_ACTIVE_CIRCLES) {
        if (!frozenCircles.empty()) {
            frozenCircles.top()->setActive(true);
            frozenCircles.pop();
        }
    }
}

void PhysicsService::checkFrozenGlasses() {
    if (!frozenGlasses.empty()) {
        GlassPhysicsObject *glass = frozenGlasses.top();
        GlassPhysicsObject *tail = firstGlass->getTail();
        float dist = glassPath.getDistanceBetweenPoints(
                tail->getShape()->getCenter(),
                glass->getShape()->getCenter()
        );
        if (dist >= glassPath.getDistanceBetweenGlasses()) {
            tail->setChild(glass);
            glass->setVisible(true);
            glass->setActive(true);
            frozenGlasses.pop();
        }
    }
}

void PhysicsService::draw(float *projMat, Shader *simpleShader, VertexBuf *vertexBuf) {
    simpleShader->beginRender(vertexBuf, 4, 4);
    simpleShader->setMVP(projMat);
    simpleShader->setColor(0, 0, 0, 1);

    if (gate->isActive()) {
        GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13};
        glDrawElements(GL_LINES, 22, GL_UNSIGNED_SHORT, indices);
    } else {
        GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 6, 7, 9, 9, 10, 10, 11, 11, 12, 12, 13};
        glDrawElements(GL_LINES, 20, GL_UNSIGNED_SHORT, indices);
    }

    simpleShader->endRender();
}