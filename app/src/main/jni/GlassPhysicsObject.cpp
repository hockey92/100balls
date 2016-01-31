#include "GlassPhysicsObject.h"
#include "GlassShape.h"
#include "CollisionFactory.h"
#include "Constants.h"

GlassPhysicsObject::GlassPhysicsObject()
        : PhysicsObject(new GlassShape(), 0.f) {
    float right = 1;
    float left = -1;
    float down = -2;
    float up = 2;

    path[0] = new Segment(Vec2(right, up), Vec2(right, down));
    path[1] = new Segment(Vec2(right, down), Vec2(left, down));
    path[2] = new Segment(Vec2(left, down), Vec2(left, up));
    path[3] = new Segment(Vec2(left, up), Vec2(right, up));
}

void GlassPhysicsObject::update() {
    float velValue  = 1.0;
    float distFromPath = 0.3;

    Vec2 dist;
    float len = 0;
    for (int i = 0; i < 4; i++) {
        Vec2 dump;
        Vec2 tempDist = CollisionFactory::createDistance(getShape()->getCenter(), path[i], dump);
        float tempLen = tempDist.len();
        if (i == 0 || tempLen < len) {
            dist = tempDist;
            len = tempLen;
        }
    }
    Vec2 norm = dist * (1 / len);
    setVel((Vec2::cross(norm, 1) * velValue) + (norm * (((len - distFromPath) * 0.1f) * DT)));
}
