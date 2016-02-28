#include "PhysicsService.h"
#include "CollisionFactory.h"
#include "Container.h"
#include "GlassPhysicsObject.h"
#include "Gate.h"
#include "common.hpp"
#include "GameCoords.h"
#include "CirclePhysicsObject.h"

void PhysicsService::addCircles(float initX, float initY, float direction, float r,
                                float distanceBetweenCircles, bool active, int numOfCircles) {
    for (int i = 0; i < numOfCircles; i++) {
        float x = initX + direction * (i % 5) * (2.0f * r + distanceBetweenCircles);
        float y = initY - (i / 5) * (2.0f * r + distanceBetweenCircles);
        PhysicsObject *po = new CirclePhysicsObject(r, 1.0f);
        if (!active) {
            frozenCircles.push(po);
        }
        po->setActive(active);
        po->getShape()->move(Vec2(x, y));
        physicsObjects.push_back(po);
        circles.push_back(po);
    }
}

PhysicsService::PhysicsService() {
    float distanceBetweenCircles = 0.005f;
    float r = GameCoords::getInstance()->getCoords(CIRCLE)->getData()[0];

    addCircles(GameCoords::getInstance()->getCoords(CONTAINER)->getData()[4] + r +
               distanceBetweenCircles,
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[5] - r -
               distanceBetweenCircles, 1.0f, r, distanceBetweenCircles, false, 30);

    addCircles(GameCoords::getInstance()->getCoords(CONTAINER)->getData()[18] - r -
               distanceBetweenCircles,
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[19] - r -
               distanceBetweenCircles, -1.0f, r, distanceBetweenCircles, false, 30);

    addCircles(-2.0f * (2.0f * r + distanceBetweenCircles),
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[19] - r -
               distanceBetweenCircles, 1.0f, r, distanceBetweenCircles, true, 40);

    container = new PhysicsObject(new Container(), 0.f);
    physicsObjects.push_back(container);

    GlassPhysicsObject *parent = NULL;
    for (int i = 0; i < 7; i++) {
        GlassPhysicsObject *po = new GlassPhysicsObject();
        po->getShape()->move(Vec2(-2.1f, 0.f));
        physicsObjects.push_back(po);
        glasses.push_back(po);
        if (parent != NULL) {
            parent->setChildren(po);
        }
        parent = po;
    }

    gate = new PhysicsObject(new Gate(), 0.f);
    physicsObjects.push_back(gate);
}

void PhysicsService::draw(float *projection) {
//    for (int i = 0; i < physicsObjects.size(); i++) {
//        physicsObjects[i]->draw(projection);
//    }
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
    int MAX_NUM_OF_ACTIVE_CIRCLES = 40;
    int numOfActiveCircles = 0;
    for (int i = 0; i < circles.size(); i++) {
        PhysicsObject *circle = circles[i];
        if (circle->isActive()) {
            numOfActiveCircles++;
            for (int j = 0; j < glasses.size(); j++) {
                PhysicsObject *glass = glasses[j];

            }
        }
    }
    if (numOfActiveCircles < MAX_NUM_OF_ACTIVE_CIRCLES) {
        if (!frozenCircles.empty()) {
            frozenCircles.top()->setActive(true);
            frozenCircles.pop();
        }
    }
}
