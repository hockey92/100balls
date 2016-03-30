#ifndef NATIVE_ACTIVITY_SIMPLEBUTTONDRAWABLE_H
#define NATIVE_ACTIVITY_SIMPLEBUTTONDRAWABLE_H

#include "ButtonDrawable.h"
#include "Font.h"

class SimpleButtonDrawable : public ButtonDrawable {
public:
    SimpleButtonDrawable();

    void draw(const DrawableData &drawableDate);

    bool init();

private:
    VertexBuff *buttonVertex;
    Font *font;
};

#endif //NATIVE_ACTIVITY_SIMPLEBUTTONDRAWABLE_H
