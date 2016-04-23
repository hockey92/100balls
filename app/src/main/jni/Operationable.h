#ifndef NATIVE_ACTIVITY_OPERATIONABLE_H
#define NATIVE_ACTIVITY_OPERATIONABLE_H

enum {
    BUTTON_EVENT_DOWN,
    BUTTON_EVENT_UP
};

class Operationable {
public:
    virtual bool doOperation(void *data) = 0;
};

#endif //NATIVE_ACTIVITY_OPERATIONABLE_H
