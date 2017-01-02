#ifndef INC_100BALLS_FONTRENDERER_H
#define INC_100BALLS_FONTRENDERER_H

#include <string>
#include "Renderer.h"

class FontRenderer : public Renderer {
public:
    void setText(const std::string& text);

protected:
    std::string text;
};

#endif //INC_100BALLS_FONTRENDERER_H
