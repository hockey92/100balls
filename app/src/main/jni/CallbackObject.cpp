#include "CallbackObject.h"
#include "Context.h"

CallbackObject::CallbackObject(std::string callbackObjectId) : callbackObjectId(callbackObjectId) {
    Context::getInstance()->getCallbackService()->addCallbackObject(this);
}

std::string CallbackObject::getCallbackObjectId() {
    return callbackObjectId;
}

void CallbackObject::addFunction(std::string functionId, CallbackFunction callbackFunction) {
    functions.put(functionId, callbackFunction);
}

void CallbackObject::callback(void *callbackData) {
    Context::getInstance()->getCallbackService()->callback(this, callbackData);
}

void CallbackObject::executeCallback(std::string functionId, void *callbackData) {
    CallbackFunction *function = functions.get(functionId);
    if (function != NULL) {
        (*function)(this, callbackData);
    }
}
