#ifndef NATIVE_ACTIVITY_INTTOKENIZER_H
#define NATIVE_ACTIVITY_INTTOKENIZER_H

class Tokenizer {
public:
    Tokenizer(unsigned int num);
    unsigned int nextToken();
    unsigned int getTokensCount();
    bool hasNext();

private:
    unsigned int size;
    unsigned int currentPos;
    unsigned int num;
};

#endif //NATIVE_ACTIVITY_INTTOKENIZER_H
