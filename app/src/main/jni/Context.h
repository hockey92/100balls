#ifndef NATIVE_ACTIVITY_CONTEXT_H
#define NATIVE_ACTIVITY_CONTEXT_H

class Context {
public:

    static void init(float w, float h);

    static Context *getInstance();

    float getW();

    float getH();

private:
    Context(float w, float h);

    static Context *instance;

    float relW;
    float relH;
};

#endif //NATIVE_ACTIVITY_CONTEXT_H
