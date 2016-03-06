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
    float *container = new float[24];

    container[0] = -0.2f, container[1] = 0.5f;
    container[2] = -0.2f, container[3] = 1.0f;
    container[4] = -1.0f + 0.405f, container[5] = 1.0f;
    container[6] = -1.0f + 0.405f, container[7] = 0.2f;
    container[8] = -0.09f, container[9] = -0.04f;
    container[10] = -0.09f, container[11] = -0.2f;
    container[12] = 0.09f, container[13] = -0.2f;
    container[14] = 0.09f, container[15] = -0.04f;
    container[16] = 1.0f - 0.405f, container[17] = 0.2f;
    container[18] = 1.0f - 0.405f, container[19] = 1.0f;
    container[20] = 0.2f, container[21] = 1.0f;
    container[22] = 0.2f, container[23] = 0.5f;

    gameCoordsData[CONTAINER] = new GameCoordsData(container, 12, CONTAINER);
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

float *GameCoordsData::createCoordsForShader(float zCoord) {
    float *result = NULL;
    switch (type) {
        case GLASS:
        case CONTAINER:
            result = new float[size * 4];
            for (int i = 0; i < size; i++) {
                result[i * 4] = data[i * 2];
                result[i * 4 + 1] = data[i * 2 + 1];
                result[i * 4 + 2] = zCoord;
                result[i * 4 + 3] = 1.0f;
            }
            break;
        case CIRCLE:
            result = new float[4 * 6];
            result[0] = -data[0], result[1] = -data[0], result[2] = zCoord, result[3] = 1.0f;
            result[4] = 0.0f, result[5] = 0.0f;
            result[6] = -data[0], result[7] = data[0], result[8] = zCoord, result[9] = 1.0f;
            result[10] = 0.0f, result[11] = 1.0f;
            result[12] = data[0], result[13] = data[0], result[14] = zCoord, result[15] = 1.0f;
            result[16] = 1.0f, result[17] = 1.0f;
            result[18] = data[0], result[19] = -data[0], result[20] = zCoord, result[21] = 1.0f;
            result[22] = 1.0f, result[23] = 0.0f;
            break;
        default:
            break;
    }
    return result;
}

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
    gameCoordsData[CIRCLE] = new GameCoordsData(0.036f, CIRCLE);
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
    screenBorders[WIDTH] = 1.0f, screenBorders[HEIGHT] = rel;
    gameCoordsData[SCREEN_BORDERS] = new GameCoordsData(screenBorders, SCREEN_BORDERS);
}

float *GameCoordsData::createCoordsForShader(float down, float up, float left, float right, float texDown,
                                   float texUp, float texLeft, float texRight) {

    float* result = new float[4 * 6];
    result[0] = left, result[1] = down, result[2] = 0, result[3] = 1.0f;
    result[4] = texLeft, result[5] = texDown;
    result[6] = left, result[7] = up, result[8] = 0, result[9] = 1.0f;
    result[10] = texLeft, result[11] = texUp;
    result[12] = right, result[13] = up, result[14] = 0, result[15] = 1.0f;
    result[16] = texRight, result[17] = texUp;
    result[18] = right, result[19] = down, result[20] = 0, result[21] = 1.0f;
    result[22] = texRight, result[23] = texDown;
    return result;
}
