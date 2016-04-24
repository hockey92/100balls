#ifndef NATIVE_ACTIVITY_SIMPLEBUTTONDRAWABLE_H
#define NATIVE_ACTIVITY_SIMPLEBUTTONDRAWABLE_H

#include "ButtonDrawer.h"
#include "Font.h"

class SimpleButtonDrawable : public ButtonDrawer {
public:
    SimpleButtonDrawable();

    void draw(const DrawableData &drawableDate);

    bool init();

    SimpleButtonDrawable * setFontColor(Color fontColor);

private:
    VertexBuff *buttonVertex;
    Font *font;
    Color fontColor;
};

#endif //NATIVE_ACTIVITY_SIMPLEBUTTONDRAWABLE_H
