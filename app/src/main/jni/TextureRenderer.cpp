#include <android/asset_manager.h>
#include "TextureRenderer.h"

TextureRenderer::TextureRenderer(struct android_app *state) {

    char fileName[] = "circle.tga";
    AAsset *m_pAsset = AAssetManager_open(state->activity->assetManager, fileName,
                                          AASSET_MODE_UNKNOWN);

    int len = AAsset_getLength(m_pAsset);
    unsigned char *buf = new unsigned char[len];
    AAsset_read(m_pAsset, (void *) buf, len);


    char vertexShader[] =
            "attribute vec4 a_vPosition; \n"
                    "attribute vec2 a_texCoord; \n"
                    "varying vec2 v_texCoord; \n"
                    "uniform mat4 projection;   \n"
                    "void main(){ \n"
                    "   gl_Position = projection * a_vPosition; \n"
                    "   v_texCoord = a_texCoord; \n"
                    "} \n";

    char fragmentShader[] =
            "precision highp float; \n"
                    "varying vec2 v_texCoord; \n"
                    "uniform sampler2D s_texture; \n"
                    "void main(){ \n"
                    "   gl_FragColor = texture2D(s_texture, v_texCoord); \n"
                    "} \n";

    program = createProgram(vertexShader, fragmentShader);

    m_positionAttributeHandle = glGetAttribLocation(program, "a_vPosition");
    m_texCoordAttributeHandle = glGetAttribLocation(program, "a_texCoord");
    m_samplerHandle = glGetUniformLocation(program, "s_texture");
//    projection = glGetUniformLocation(program, "projection");

    glGenTextures(1, &id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    TGAHeader* header = (TGAHeader*) buf;

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            ((TGAHeader *) buf)->m_width,
            ((TGAHeader *) buf)->m_height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            (buf + sizeof(TGAHeader))
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void TextureRenderer::render(float *pm) {
    float r = 0.06;
    GLfloat vVertices[] = {-r, -r, 0.0f, // Position 0
                           0.0f, 0.0f, // TexCoord 0
                           -r, r, 0.0f, // Position 1
                           0.0f, 1.0f, // TexCoord 1
                           r, r, 0.0f, // Position 2
                           1.0f, 1.0f, // TexCoord 2
                           r, -r, 0.0f, // Position 3
                           1.0f, 0.0f // TexCoord 3
    };

    GLushort indices[] = {0, 1, 2, 0, 2, 3};
    GLsizei stride = 5 * sizeof(GLfloat); // 3 for position, 2 for texture

    glUseProgram(program);
    // Load the vertex position
    glVertexAttribPointer(m_positionAttributeHandle, 3, GL_FLOAT, GL_FALSE, stride,
                          vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(m_texCoordAttributeHandle, 2, GL_FLOAT, GL_FALSE, stride,
                          &vVertices[3]);

    glEnableVertexAttribArray(m_positionAttributeHandle);
    glEnableVertexAttribArray(m_texCoordAttributeHandle);

    glUniformMatrix4fv(projection, 1, GL_FALSE, pm);
//
//    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    // Set the sampler texture unit to 0
    glUniform1i(m_samplerHandle, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}
