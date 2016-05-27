#ifndef NATIVE_ACTIVITY_BUTTONDRAWABLE_H
#define NATIVE_ACTIVITY_BUTTONDRAWABLE_H

#include "Drawable.h"
#include "ButtonData.h"

class ButtonDrawer : public Drawable {
public:
    virtual void setButtonData(ButtonData *buttonData);

    virtual ButtonDrawer *setColor(const Color &color);

    virtual void draw(const DrawableData &drawableDate) = 0;

    virtual unsigned int type() { return 0; };

    virtual bool init() { }

    virtual Initializer *createInitializer() {
        return NULL;
    }

protected:
    virtual void afterButtonDataIsDefined() { }

    ButtonData *buttonData;
    Color color;
};

#endif //NATIVE_ACTIVITY_BUTTONDRAWABLE_H
