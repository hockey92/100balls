#include "ButtonData.h"

ButtonData::ButtonData(const AABB &aabb, const Vec2 &center) : _pushed(false), _center(center), _text("") {
    _aabb = new AABB(aabb);
    _aabb->move(center);
}

ButtonData::~ButtonData() {
    if (_aabb) {
        delete _aabb;
    }
}
