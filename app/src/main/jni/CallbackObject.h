#ifndef NATIVE_ACTIVITY_CALLBACKOBJECT_H
#define NATIVE_ACTIVITY_CALLBACKOBJECT_H

#include <string>
#include <map>
#include "MapWrapper.h"

class CallbackObject;

typedef void (*CallbackFunction)(CallbackObject *, void *);

class CallbackObject {
public:
    CallbackObject(std::string callbackObjectId);

    std::string getCallbackObjectId();

    void executeCallback(std::string functionId, void *callbackData);

protected:
    void addFunction(std::string functionId, CallbackFunction callbackFunction);

    void callback(void *callbackData);

private:
    std::string callbackObjectId;
    MapWrapper<std::string, CallbackFunction> functions;
};

#endif //NATIVE_ACTIVITY_CALLBACKOBJECT_H
