#ifndef NATIVE_ACTIVITY_TOUCHEVENTDATA_H
#define NATIVE_ACTIVITY_TOUCHEVENTDATA_H

#include "Vec2.h"

struct TouchEventData {

    TouchEventData(int code, const Vec2 &position, int touchId) : type(code), position(position), touchId(touchId) { }

    int type;
    Vec2 position;
    int touchId;
};

#endif //NATIVE_ACTIVITY_TOUCHEVENTDATA_H
