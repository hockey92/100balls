#ifndef NATIVE_ACTIVITY_OPERATIONABLE_H
#define NATIVE_ACTIVITY_OPERATIONABLE_H

enum {
    EVENT_DOWN,
    EVENT_UP
};

class Operationable {
public:
    virtual bool doOperation(void *data) = 0;
};

#endif //NATIVE_ACTIVITY_OPERATIONABLE_H
