#ifndef NATIVE_ACTIVITY_SCREEN_H
#define NATIVE_ACTIVITY_SCREEN_H

#include "Operationable.h"
#include <vector>

class ScreenElement : public Operationable {
public:
    virtual bool init();

    virtual void doFrame(float *projMat);

    void addScreenElement(ScreenElement *screenElement);

    bool doOperation(void *data);

protected:
    std::vector<ScreenElement *> screenElements;
};

#endif //NATIVE_ACTIVITY_SCENE_H
