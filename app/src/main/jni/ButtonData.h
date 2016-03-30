#ifndef NATIVE_ACTIVITY_BUTTONDATA_H
#define NATIVE_ACTIVITY_BUTTONDATA_H

#include "Vec2.h"
#include "AABB.h"
#include <string>

class ButtonData {
public:
    ButtonData(const AABB &aabb, const Vec2 &center);

    ~ButtonData();

    bool pushed() const { return _pushed; }

    Vec2 &center() { return _center; }

    std::string &text() { return _text; }

    AABB *aabb() const { return _aabb; }

    void setPushed(bool pushed) { _pushed = pushed; }

    void setText(std::string text) { _text = text; }

private:
    bool _pushed;
    AABB *_aabb;
    Vec2 _center;
    std::string _text;
};

#endif //NATIVE_ACTIVITY_BUTTONDATA_H
