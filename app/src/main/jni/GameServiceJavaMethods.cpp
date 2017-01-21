#include <jni.h>
#include "ServiceManager.h"

extern "C" {

GameService *getGameService() {
    return ServiceManager::getInstance()->getGameService();
}

JNIEXPORT void JNICALL
Java_com_android_game_GameService_draw(JNIEnv *env, jclass type, jfloat time) {
    getGameService()->draw(time);
}

JNIEXPORT void JNICALL
Java_com_android_game_GameService_resetNative(JNIEnv *env, jclass type) {
    getGameService()->reset();
}

JNIEXPORT void JNICALL
Java_com_android_game_GameService_nextFrameNative(JNIEnv *env, jclass type, jfloat dt) {
    getGameService()->nextFrame(dt);
}

JNIEXPORT void JNICALL
Java_com_android_game_GameService_openNative(JNIEnv *env, jclass type) {
    getGameService()->open();
}

JNIEXPORT void JNICALL
Java_com_android_game_GameService_closeNative(JNIEnv *env, jclass type) {
    getGameService()->close();
}

}
