#ifndef NATIVE_ACTIVITY_SCREENELEMENT_H
#define NATIVE_ACTIVITY_SCREENELEMENT_H

#include "Operationable.h"
#include "Shader.h"
#include "TextureShader.h"
#include <vector>

class ScreenElement : public Operationable, public OpenGLObject {
public:
    ScreenElement() : isActive(true) { }

    virtual ~ScreenElement();

    virtual bool init();

    virtual void kill();

    virtual void draw(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    virtual void draw(float *projMat);

    void addScreenElement(ScreenElement *screenElement);

    virtual bool doOperation(void *data);

    virtual void beforeDraw() { }

    void setActive(bool isActive);

protected:
    std::vector<ScreenElement *> screenElements;
    bool isActive;
};

#endif //NATIVE_ACTIVITY_SCREENELEMENT_H
