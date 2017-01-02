#include "GLFontRenderer.h"

void GLFontRenderer::render() {
    font->renderText(text, x, y);
}

GLFontRenderer::GLFontRenderer(Font *font) : font(font) {

}
