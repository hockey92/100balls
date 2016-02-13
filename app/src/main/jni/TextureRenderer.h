#ifndef NATIVE_ACTIVITY_TEXTURERENDERER_H
#define NATIVE_ACTIVITY_TEXTURERENDERER_H

#include "BaseRenderer.h"
#include "Renderer.h"
#include <android_native_app_glue.h>

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

class TextureRenderer : public Renderer {
public:
    TextureRenderer(struct android_app *state);

    virtual void render(float *pm);

private:
    GLuint id;
    GLint m_positionAttributeHandle;
    GLint m_texCoordAttributeHandle;
    GLint m_samplerHandle;

    GLuint program;
};

#endif //NATIVE_ACTIVITY_TEXTURERENDERER_H
