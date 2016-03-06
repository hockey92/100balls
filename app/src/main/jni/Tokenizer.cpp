#include "Tokenizer.h"

unsigned int Tokenizer::nextToken() {
    currentPos++;
    if (num < 10) {
        return num;
    }
    int prevNum = num;
    num /= 10;
    return prevNum - num * 10;
}

Tokenizer::Tokenizer(unsigned int num) {
    this->num = num;
    size = 1;
    currentPos = 0;
    while (true) {
        num /= 10;
        if (!num) break;
        size++;
    }
}

unsigned int Tokenizer::getTokensCount() {
    return size;
}

bool Tokenizer::hasNext() {
    return currentPos < size;
}
