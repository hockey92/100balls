#include "CallbackService.h"

void CallbackService::callback(CallbackObject *callbackObject, void *callbackData) {
    CallbackInfo *callbackInfo = callbackLinks.get(callbackObject->getCallbackObjectId());
    if (callbackInfo != NULL) {
        CallbackObject **receiver = callbackObjectsById.get(callbackInfo->getReceiverId());
        if (receiver != NULL) {
            (*receiver)->executeCallback(callbackInfo->getFunctionId(), callbackData);
        }
    }
}

void CallbackService::addCallbackLink(std::string transmitterId, std::string receiverId, std::string receiverFunctionId) {
    callbackLinks.put(transmitterId, CallbackInfo(receiverId, receiverFunctionId));
}

void CallbackService::addCallbackObject(CallbackObject *callbackObject) {
    callbackObjectsById.put(callbackObject->getCallbackObjectId(), callbackObject);
}

CallbackService::CallbackService() {
    addCallbackLink("menuStartButton", "screenManager", "callbackPushStartButton");
    addCallbackLink("menuContinueButton", "screenManager", "callbackPushContinueButton");
    addCallbackLink("gameFieldPauseButton", "screenManager", "callbackPushPauseButton");
    addCallbackLink("gamePhysicsService", "screenManager", "callbackGameOver");
    addCallbackLink("gameOverRestartButton", "screenManager", "callbackPushStartButton");
    addCallbackLink("gameOverMenuButton", "screenManager", "callbackPushPauseButton");
}
