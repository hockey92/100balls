#ifndef NATIVE_ACTIVITY_CALLBACKSERVICE_H
#define NATIVE_ACTIVITY_CALLBACKSERVICE_H

#include "CallbackObject.h"

class CallbackInfo {
public:
    CallbackInfo(std::string callbackObjectId, std::string functionId)
            : callbackObjectId(callbackObjectId),
              functionId(functionId) { }

    std::string getReceiverId() {
        return callbackObjectId;
    }

    std::string getFunctionId() {
        return functionId;
    }

private:
    std::string callbackObjectId;
    std::string functionId;
};

class CallbackService {
public:
    CallbackService();

    void callback(CallbackObject *callbackObject);

    void addCallbackObject(CallbackObject *callbackObject);

private:
    void addCallbackLink(std::string transmitterId, std::string receiverId, std::string receiverFunctionId);

    MapWrapper<std::string, CallbackObject *> callbackObjectsById;
    MapWrapper<std::string, CallbackInfo> callbackLinks;

    std::map<std::string, CallbackObject *> qwerty;

};

#endif //NATIVE_ACTIVITY_CALLBACKSERVICE_H
