#ifndef NATIVE_ACTIVITY_CONTEXT_H
#define NATIVE_ACTIVITY_CONTEXT_H

enum {
    CONTAINER, CIRCLE
};

class GameCoordsData {
public:
    GameCoordsData(float *flatCoords, int size, int type);

    GameCoordsData(float *flatCoords, int type);

    GameCoordsData(float value, int type);

    ~GameCoordsData();

    float *getData();

    int getSize();

    int getType();

private:
    float *data;
    int size;
    int type;
};

class Context {
public:
    ~Context();

    GameCoordsData *getCoords(int type);

    static void init(float w, float h);

    static Context *getInstance();

    float getW();

    float getH();

private:
    Context(float w, float h);

    GameCoordsData *gameCoordsData[4];

    static Context *instance;

    void createContainerCoords(float w, float h);

    float relW;
    float relH;
};

#endif //NATIVE_ACTIVITY_CONTEXT_H
