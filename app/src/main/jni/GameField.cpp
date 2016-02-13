#include "GameField.h"

void GameField::init() {
    textureShader = new TextureShader();
    textureShader->compile();

    float r = 0.5f;

    GLfloat vertices[] = {-r, -r, 0.0f, // Position 0
                        0.0f, 0.0f, // TexCoord 0
                        -r, r, 0.0f, // Position 1
                        0.0f, 1.0f, // TexCoord 1
                        r, r, 0.0f, // Position 2
                        1.0f, 1.0f, // TexCoord 2
                        r, -r, 0.0f, // Position 3
                        1.0f, 0.0f // TexCoord 3
    };

    vertexBuf = new VertexBuf(&vertices[0], 20);

    texture = new Texture();
}
