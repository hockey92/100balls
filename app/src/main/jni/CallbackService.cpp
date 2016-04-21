#include "CallbackService.h"

void CallbackService::callback(CallbackObject *callbackObject) {
    CallbackInfo *callbackInfo = callbackLinks.get(callbackObject->getCallbackObjectId());
    if (callbackInfo != NULL) {
        CallbackObject **receiver = callbackObjectsById.get(callbackInfo->getReceiverId());
        if (receiver != NULL) {
            (*receiver)->executeCallback(callbackInfo->getFunctionId(), NULL);
        }
    }
}

void CallbackService::addCallbackLink(std::string transmitterId,
                                      std::string receiverId,
                                      std::string receiverFunctionId) {
    callbackLinks.put(transmitterId, CallbackInfo(receiverId, receiverFunctionId));
}

void CallbackService::addCallbackObject(CallbackObject *callbackObject) {
    callbackObjectsById.put(callbackObject->getCallbackObjectId(), callbackObject);
    bool exist = callbackObjectsById.contains(callbackObject->getCallbackObjectId());
    int i = 0;
}

CallbackService::CallbackService() {
    addCallbackLink("menuStartButton", "screenManager", "callbackPushStartButton");
}
