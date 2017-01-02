#include <jni.h>
#include "ServiceManager.h"
#include "ObjectsPool.h"

extern "C" {

FontRenderer *fontRenderer = NULL;
RendererFactory* rendererFactory = NULL;
ObjectsPool<Renderer> renderers;

FontRenderer *getFontRenderer() {
    if (!fontRenderer) {
        fontRenderer = ServiceManager::getInstance()->getScreenService()->getRendererFactory()->createFontRenderer();
    }
    return fontRenderer;
}

RendererFactory *getRendererFactory() {
    if (!rendererFactory) {
        rendererFactory = ServiceManager::getInstance()->getScreenService()->getRendererFactory();
    }
    return rendererFactory;
}

JNIEXPORT jint JNICALL
Java_com_android_game_Renderer_render(JNIEnv *env, jclass type, jint id) {
    Renderer* renderer = renderers.getObject(id);
    renderer->setColor(Color(1, 1, 1, 1));
    renderer->render();
}

JNIEXPORT jint JNICALL
Java_com_android_game_Renderer_setPosition(JNIEnv *env, jclass type, jint id, jfloat x, jfloat y) {
    Renderer* renderer = renderers.getObject(id);
    renderer->setPosition(x, y);
}

JNIEXPORT jint JNICALL
Java_com_android_game_Renderer_createTextureRenderer(JNIEnv *env, jclass type, jstring text, jfloat w, jfloat h) {
    const char *c_str = env->GetStringUTFChars(text, 0);
    Renderer *renderer = getRendererFactory()->createTextureRenderer(w, h, c_str);
    env->ReleaseStringUTFChars(text, c_str);
    int index = renderers.addNewObject(renderer);
    return index;
}

JNIEXPORT void JNICALL
Java_com_android_game_Font_render(JNIEnv *env, jclass type, jstring text, jfloat x, jfloat y) {
    const char *c_str = env->GetStringUTFChars(text, 0);
    getFontRenderer()->setText(c_str);
    getFontRenderer()->setPosition(x, y);
    getFontRenderer()->render();
    env->ReleaseStringUTFChars(text, c_str);
}

}
