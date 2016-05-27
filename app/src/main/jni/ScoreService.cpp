#include "ScoreService.h"
#include "Constants.h"

unsigned int ScoreService::getTotal() {
    return total;
}

float ScoreService::getGlassVel() {
    float vel = INIT_GLASS_VEL - 0.05f * (float) (total / 100);
    return vel > 2.0f ? 2.0f : vel;
}

void ScoreService::add(int score) {
    total += score;
}

void ScoreService::reset() {
    total = 0;
}

ScoreService::ScoreService() {
    reset();
}
