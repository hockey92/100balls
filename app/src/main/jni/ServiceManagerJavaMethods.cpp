#include <jni.h>
#include "ServiceManager.h"

extern "C" {

ServiceManager *getServiceManager() {
    return ServiceManager::getInstance();
}

JNIEXPORT void JNICALL
Java_com_android_game_ServiceManager_init(JNIEnv *env, jclass type, jobject assetManager) {
    getServiceManager()->init(AAssetManager_fromJava(env, assetManager));
}

}
