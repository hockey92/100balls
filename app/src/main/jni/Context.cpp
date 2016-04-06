#include <stddef.h>
#include "Context.h"

Context *Context::instance = NULL;

GameCoordsData *Context::getCoords(int type) {
    return gameCoordsData[type];
}

Context::Context(float w, float h) {

    float rel = h / w;

    relW = 1.0f;
    relH = rel;

    createContainerCoords(w, h);
}

Context::~Context() {
    for (int i = 0; i < 2; i++) {
        delete gameCoordsData[i];
    }
}

void Context::createContainerCoords(float w, float h) {
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

Context *Context::getInstance() {
    return Context::instance;
}

void Context::init(float w, float h) {
    if (Context::instance == NULL) {
        Context::instance = new Context(w, h);
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


float Context::getW() {
    return relW;
}

float Context::getH() {
    return relH;
}
