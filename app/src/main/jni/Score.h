#ifndef INC_100BALLS_SCORE_H
#define INC_100BALLS_SCORE_H

class Score {
public:
    Score() : score(0) { }

    void add(int toAdd);

    int getValue();

    void reset();

private:
    int score;
};

#endif //INC_100BALLS_SCORE_H
