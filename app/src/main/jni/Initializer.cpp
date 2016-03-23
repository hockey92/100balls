#include "Initializer.h"

void Initializer::endRender(Shader *simpleShader, TextureShader *textureShader) {
    simpleShader->endRender();
    textureShader->endRender();
}
