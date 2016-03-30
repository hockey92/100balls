#include <stddef.h>
#include "GameCoords.h"

GameCoords *GameCoords::instance = NULL;

GameCoordsData *GameCoords::getCoords(int type) {
    return gameCoordsData[type];
}

GameCoords::GameCoords(float w, float h) {
    createGlassCoords(w, h);
    createCircleCoords(w, h);
    createPathCoordsAndScreenBorders(w, h);
    createContainerCoords(w, h);
}

GameCoords::~GameCoords() {
    for (int i = 0; i < 2; i++) {
        delete gameCoordsData[i];
    }
}

void GameCoords::createGlassCoords(float w, float h) {
    float *glass = new float[8];

    float d = 0.2f;

    float left = -d * 0.8f;
    float down = -d;
    float right = d * 0.8f;
    float up = d;

    glass[0] = left, glass[1] = up;
    glass[2] = 0.65f * left, glass[3] = down;
    glass[4] = 0.65f * right, glass[5] = down;
    glass[6] = right, glass[7] = up;

    gameCoordsData[GLASS] = new GameCoordsData(glass, 4, GLASS);
}

void GameCoords::createContainerCoords(float w, float h) {
    float *container = new float[28];

    container[0] = -0.2f, container[1] = 0.5f;
    container[2] = -0.2f, container[3] = 1.0f;
    container[4] = -1.0f + 0.405f, container[5] = 1.0f;
    container[6] = -1.0f + 0.405f, container[7] = 0.25f;
    container[8] = -0.09f, container[9] = 0.05f;
    container[10] = -0.09f, container[11] = -0.13f;

    container[12] = -0.09f, container[13] = -0.22f;
    container[14] = 0.09f, container[15] = -0.22f;

    container[16] = 0.09f, container[17] = -0.13f;
    container[18] = 0.09f, container[19] = 0.05f;
    container[20] = 1.0f - 0.405f, container[21] = 0.25f;
    container[22] = 1.0f - 0.405f, container[23] = 1.0f;
    container[24] = 0.2f, container[25] = 1.0f;
    container[26] = 0.2f, container[27] = 0.5f;

    gameCoordsData[CONTAINER] = new GameCoordsData(container, 14, CONTAINER);
}

GameCoords *GameCoords::getInstance() {
    return GameCoords::instance;
}

void GameCoords::init(float w, float h) {
    if (GameCoords::instance == NULL) {
        GameCoords::instance = new GameCoords(w, h);
    }
}

GameCoordsData::GameCoordsData(float *flatCoords, int type) : data(flatCoords), size(0),
                                                              type(type) { }

GameCoordsData::GameCoordsData(float value, int type) : size(0), type(type) {
    data = new float[1];
    data[0] = value;
}

GameCoordsData::GameCoordsData(float *flatCoords, int size, int type) : data(flatCoords),
                                                                        size(size), type(type) { }

GameCoordsData::~GameCoordsData() { delete[] data; }

float *GameCoordsData::getData() { return data; }

int GameCoordsData::getSize() { return size; }

int GameCoordsData::getType() { return type; }

void GameCoords::createCircleCoords(float w, float h) {
    gameCoordsData[CIRCLE] = new GameCoordsData(0.0355f, CIRCLE);
}

void GameCoords::createPathCoordsAndScreenBorders(float w, float h) {
    float *path = new float[5];

    float rel = h / w;

    float left = -0.6f;
    float down = -rel + 0.44f;
    float right = 0.6f;
    float up = rel - 0.44f;

    path[LEFT] = left;
    path[DOWN] = down;
    path[RIGHT] = right;
    path[UP] = up;

    path[DIST_FROM_PATH] = 0.2f;

    gameCoordsData[PATH] = new GameCoordsData(path, PATH);

    float *screenBorders = new float[2];
    screenBorders[WIDTH] = 1.0f, screenBorders[HIGH] = rel;
    gameCoordsData[SCREEN_BORDERS] = new GameCoordsData(screenBorders, SCREEN_BORDERS);
}

