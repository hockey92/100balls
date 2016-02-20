#include <vecmath.h>
#include "BaseShape.h"

void BaseShape::move(const Vec2& coords) {
    center += coords;
}

Vec2 BaseShape::getCenter() const {
    if (parent != NULL) {
        return parent->getCenter();
    }
    return center;
}

void BaseShape::draw(float *projection) {
//    if (renderer != NULL) {
//        ndk_helper::Mat4 translation = ndk_helper::Mat4::Translation(center.x(), center.y(), 0.f);
//        ndk_helper::Mat4 projectionMat = ndk_helper::Mat4(projection);
//        ndk_helper::Mat4 rotationMat = ndk_helper::Mat4::RotationZ(angle);
//
//        renderer->render((projectionMat * translation * rotationMat).Ptr());
//    }
}

BaseShape *BaseShape::getChildren(int i) {
    if (realChildCount == 0) {
        return this;
    }
    return children[i];
}

void BaseShape::rotate(const float angle) {
    for (int i = 0; i < realChildCount; i++) {
        getChildren(i)->rotate(angle);
    }
    innerRotate(angle);
}

void BaseShape::innerRotate(float angle) {
    this->angle += angle;
}

float BaseShape::getAngel() const {
    if (parent != NULL) {
        return parent->getAngel();
    }
    return angle;
}

int BaseShape::getChildCount() const {
    return realChildCount == 0 ? 1 : realChildCount;
}