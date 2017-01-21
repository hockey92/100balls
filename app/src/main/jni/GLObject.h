#ifndef INC_100BALLS_OPENGLOBJECTS_H
#define INC_100BALLS_OPENGLOBJECTS_H

#include <Mutex.h>

class GLObject {
public:
    GLObject();

    void init();

    virtual void kill() = 0;

    virtual void render() { }

    void prepareRender();

    virtual bool equals(const GLObject &b) const { return false; }

    static void incrementNumberOfInits();

    int getId();

protected:
    virtual void innerPrepareRender() { };

    virtual void innerInit() = 0;

private:
    int initIndex;
    static int numberOfInits;
    int id;
    static int lastId;
    static Mutex mutex;
};

#endif //INC_100BALLS_OPENGLOBJECTS_H
