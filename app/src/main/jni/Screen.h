#ifndef NATIVE_ACTIVITY_SCREEN_H
#define NATIVE_ACTIVITY_SCREEN_H

class Screen {
public:
    Screen(float w, float h) : _w(w), _h(h) { }

    float w() { return _w; }

    float h() { return _h; }

private:
    Screen() { }

    float _w;
    float _h;
};

#endif //NATIVE_ACTIVITY_SCREEN_H
