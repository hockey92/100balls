#include <jni.h>
#include "ScreenService.h"
#include "ServiceManager.h"

extern "C" {

ScreenService *getScreenService() {
    return ServiceManager::getInstance()->getScreenService();
}

JNIEXPORT void JNICALL
Java_com_android_game_ScreenService_surfaceCreated(JNIEnv *env, jclass type, jobject assetManager) {
    getScreenService()->surfaceCreated();
}

JNIEXPORT void JNICALL
Java_com_android_game_ScreenService_surfaceChangedNative(JNIEnv *env, jclass type,
                                                         jint width, jint height) {
    getScreenService()->surfaceChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_android_game_ScreenService_beforeDraw(JNIEnv *env, jclass type) {
    getScreenService()->beforeDraw();
}

}
