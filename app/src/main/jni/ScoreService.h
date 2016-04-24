#ifndef NATIVE_ACTIVITY_SCORESERVICE_H
#define NATIVE_ACTIVITY_SCORESERVICE_H

class ScoreService {
public:
    ScoreService();

    unsigned int getTotal();

    float getGlassVel();

    void add(int score);

    void reset();

private:
    unsigned int total;
    float initGlassVel;
};

#endif //NATIVE_ACTIVITY_SCORESERVICE_H
