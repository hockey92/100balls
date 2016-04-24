#include "ScoreService.h"

unsigned int ScoreService::getTotal() {
    return total;
}

float ScoreService::getGlassVel() {
    float vel = initGlassVel - 0.05f * (float) (total / 100);
    return vel > 2.0f ? 2.0f : vel;
}

void ScoreService::add(int score) {
    total += score;
}

void ScoreService::reset() {
    total = 0;
    initGlassVel = -0.3f;
}

ScoreService::ScoreService() {
    reset();
}
