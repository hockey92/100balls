#include <vecmath.h>
#include "BaseShape.h"

void BaseShape::move(const Vec2& coords) {
    center += coords;
}

Vec2 BaseShape::getCenter() const {
    return center;
}

void BaseShape::draw(float *projection) {
    ndk_helper::Mat4 translation = ndk_helper::Mat4::Translation(center.x(), center.y(), 0.f);
    ndk_helper::Mat4 projectionMat = ndk_helper::Mat4(projection);

    renderer->render((projectionMat * translation).Ptr());
}

BaseShape *BaseShape::getChildren(int i) {
    if (childCount == 0) {
        return NULL;
    }
    return children[i];
}
