#ifndef NATIVE_ACTIVITY_CONTEXT_H
#define NATIVE_ACTIVITY_CONTEXT_H

enum {
    GLASS, CONTAINER, BALL, PATH
};

enum {
    LEFT, DOWN, RIGHT, UP, DIST_FROM_PATH
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

    float *createCoordsForShader(float zCoord);

private:
    float *data;
    int size;
    int type;
};

class GameCoords {
public:
    GameCoords(float w, float h);

    ~GameCoords();

    GameCoordsData *getCoords(int type);

    static void init(float w, float h);

    static GameCoords *getInstance();

private:
    GameCoordsData *gameCoordsData[4];

    static GameCoords *instance;

    void createGlassCoords(float w, float h);

    void createContainerCoords(float w, float h);

    void createCircleCoords(float w, float h);

    void createPathCoords(float w, float h);
};

#endif //NATIVE_ACTIVITY_CONTEXT_H