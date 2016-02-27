#include "PhysicsService.h"
#include "CollisionFactory.h"
#include "Container.h"
#include "GlassPhysicsObject.h"
#include "Gate.h"
#include "common.hpp"
#include "GameCoords.h"

void PhysicsService::addCircles(float initX, float initY, float direction, float r,
                                float distanceBetweenCircles, bool active, int numOfCircles) {
    for (int i = 0; i < numOfCircles; i++) {
        float x = initX + direction * (i % 5) * (2.0f * r + distanceBetweenCircles);
        float y = initY - (i / 5) * (2.0f * r + distanceBetweenCircles);
        PhysicsObject *po = new PhysicsObject(new Circle(r), 1.0f);
        po->setActive(active);
        po->getShape()->move(Vec2(x, y));
        physicsObjects.push_back(po);
    }
}

PhysicsService::PhysicsService() {
    float distanceBetweenCircles = 0.005f;
    float r = GameCoords::getInstance()->getCoords(BALL)->getData()[0];

    addCircles(GameCoords::getInstance()->getCoords(CONTAINER)->getData()[4] + r +
               distanceBetweenCircles,
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[5] - r -
               distanceBetweenCircles, 1.0f, r, distanceBetweenCircles, false, 45);

    addCircles(GameCoords::getInstance()->getCoords(CONTAINER)->getData()[18] - r -
               distanceBetweenCircles,
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[19] - r -
               distanceBetweenCircles, -1.0f, r, distanceBetweenCircles, false, 45);

    addCircles(-2.0f * (2.0f * r + distanceBetweenCircles),
               GameCoords::getInstance()->getCoords(CONTAINER)->getData()[19] - r -
               distanceBetweenCircles, 1.0f, r, distanceBetweenCircles, true, 40);

    physicsObjects.push_back(new PhysicsObject(new Container(), 0.f));

    GlassPhysicsObject *po1 = new GlassPhysicsObject();
    po1->getShape()->move(Vec2(2.1f, 0.f));
    physicsObjects.push_back(po1);

    GlassPhysicsObject *parent = po1;
    for (int i = 0; i < 6; i++) {
        GlassPhysicsObject *po2 = new GlassPhysicsObject();
        po2->getShape()->move(Vec2(-2.1f, 0.f));
        physicsObjects.push_back(po2);

        parent->setChildren(po2);
        parent = po2;
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
