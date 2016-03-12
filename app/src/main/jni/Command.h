#ifndef NATIVE_ACTIVITY_COMMAND_H
#define NATIVE_ACTIVITY_COMMAND_H

class Command {
public:
    virtual void *execute(void *data) = 0;
};

#endif //NATIVE_ACTIVITY_COMMAND_H
