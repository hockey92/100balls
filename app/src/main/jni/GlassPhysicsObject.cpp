#include "GlassPhysicsObject.h"
#include "GlassShape.h"
#include "CollisionFactory.h"
#include "Constants.h"

GlassPhysicsObject::GlassPhysicsObject()
        : PhysicsObject(new GlassShape(), 0.f) {
    float right = 1.5f;
    float left = -1.5f;
    float down = -3;
    float up = 1.0f;

    path[0] = new Segment(Vec2(right, up), Vec2(right, down));
    path[1] = new Segment(Vec2(right, down), Vec2(left, down));
    path[2] = new Segment(Vec2(left, down), Vec2(left, up));
    path[3] = new Segment(Vec2(left, up), Vec2(right, up));
}

void GlassPhysicsObject::update() {
    float velValue  = -1.5f;
    float distFromPath = 0.3f;

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
    setVel((Vec2::cross(norm, 1) * velValue) + (norm * (((len - distFromPath) * 0.1f) / DT)));
}
