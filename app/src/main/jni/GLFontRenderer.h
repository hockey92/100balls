#ifndef INC_100BALLS_GLFONTRENDERER_H
#define INC_100BALLS_GLFONTRENDERER_H

#include "FontRenderer.h"
#include "Font.h"

class GLFontRenderer : public FontRenderer{
public:
    GLFontRenderer(Font* font);

    void render();

private:
    Font* font;
};


#endif //INC_100BALLS_GLFONTRENDERER_H
