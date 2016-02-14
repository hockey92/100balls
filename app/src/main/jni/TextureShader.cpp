#include <GLES2/gl2.h>
#include "TextureShader.h"
#include "common.hpp"

struct TGAHeader {
    unsigned char m_idSize;
    unsigned char m_colorMapType;
    unsigned char m_imageType;
    unsigned short m_paletteStart;
    unsigned short m_paletteLength;
    unsigned char m_paletteBits;
    unsigned short m_xOrigin;
    unsigned short m_yOrigin;
    unsigned short m_width;
    unsigned short m_height;
    unsigned char m_bpp;
    unsigned char m_descriptor;
} __attribute__ ((packed));

const char *TextureShader::getShaderName() {
    return "TextureShader";
}

const char *TextureShader::getFragmentShaderSource() {
    return "precision highp float; \n"
            "varying vec2 v_texCoord; \n"
            "uniform sampler2D s_texture; \n"
            "void main(){ \n"
            "   gl_FragColor = texture2D(s_texture, v_texCoord); \n"
            "} \n";
}

const char *TextureShader::getVertexShaderSource() {
    return "attribute vec4 a_Position; \n"
            "attribute vec2 a_texCoord; \n"
            "varying vec2 v_texCoord; \n"
            "uniform mat4 projection;   \n"
            "void main(){ \n"
            "   gl_Position = projection * a_Position; \n"
            "   v_texCoord = a_texCoord; \n"
            "} \n";
}

void TextureShader::compile() {
    Shader::compile();

    bindShader();
    texCoordAttributeHandle = glGetAttribLocation(program, "a_texCoord");
    if (texCoordAttributeHandle < 0) {
        LOGE("*** Couldn't get shader's a_texCoord location.");
        ABORT_GAME;
    }
    samplerHandle = glGetUniformLocation(program, "s_texture");
    if (samplerHandle < 0) {
        LOGE("*** Couldn't get shader's s_texture location.");
        ABORT_GAME;
    }
    unbindShader();
}

void TextureShader::setTexture(Texture *texture) {
    MY_ASSERT(preparedVertexBuf != NULL);
    texture->bind(GL_TEXTURE0);
    glUniform1i(samplerHandle, 0);
}

void TextureShader::beginRender(VertexBuf *vbuf) {
    Shader::beginRender(vbuf);

    glVertexAttribPointer(texCoordAttributeHandle, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          BUFFER_OFFSET(3));
    glEnableVertexAttribArray(texCoordAttributeHandle);
}
