#ifndef NATIVE_ACTIVITY_SCORESERVICE_H
#define NATIVE_ACTIVITY_SCORESERVICE_H

class ScoreService {
public:
    int getTotal();
    float getGlassVel();
    void add(int score);
    void reset();
    static ScoreService* getInstance();

private:
    ScoreService();
    static ScoreService* instance;
    int total;
    float initGlassVel;
};

#endif //NATIVE_ACTIVITY_SCORESERVICE_H
