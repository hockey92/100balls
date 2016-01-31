#include <vecmath.h>
#include "BaseShape.h"

void BaseShape::move(const Vec2& coords) {
//    pthread_mutex_lock(&mutex);
    center += coords;
//    pthread_mutex_unlock(&mutex);
}

Vec2 BaseShape::getCenter() const {
    return center;
}

void BaseShape::draw(float *projection) {
//    pthread_mutex_lock(&mutex);
    ndk_helper::Mat4 translation = ndk_helper::Mat4::Translation(center.x(), center.y(), 0.f);
    ndk_helper::Mat4 projectionMat = ndk_helper::Mat4(projection);
//    pthread_mutex_unlock(&mutex);

    renderer->render((projectionMat * translation).Ptr());
}

BaseShape *BaseShape::getChildren(int i) {
    if (childCount == 0) {
        return NULL;
    }
    return children[i];
}
