#ifndef NATIVE_ACTIVITY_SCREEN_H
#define NATIVE_ACTIVITY_SCREEN_H

#include "ArrayWrapper.h"

class Screen {
public:
    Screen(float realW, float realH);

    float w() const { return _w; }

    float h() const { return _h; }

    float realW() { return _realW; }

    float realH() { return _realH; }

    float *projMat() const { return _projMat.ptr(); }

private:
    Screen() { }

    float _w;
    float _h;

    float _realW;
    float _realH;

    ArrayWrapper _projMat;
};

#endif //NATIVE_ACTIVITY_SCREEN_H
