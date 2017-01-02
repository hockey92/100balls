#include "Score.h"

int Score::getValue() {
    return score;
}

void Score::add(int toAdd) {
    score += toAdd;
}

void Score::reset() {
    score = 0;
}
