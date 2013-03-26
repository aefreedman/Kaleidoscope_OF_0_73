#ifndef STRANDEDASTRONAUT_H
#define STRANDEDASTRONAUT_H

#include "Astronaut.h"


class StrandedAstronaut : public Astronaut {
public:
    StrandedAstronaut();
    StrandedAstronaut(ofVec2f _pos);
    virtual ~StrandedAstronaut();
    void update();
    void draw();
    void move();
    void detectPlayerCollisions();
    void followPlayer();
    void getPlayerData(ofVec2f _player_pos);
    int r;
    bool FOLLOWING_PLAYER;
protected:

private:
    ofVec2f a;
    ofVec2f v;
    ofVec2f f;
    ofVec2f player_pos;

};

#endif // STRANDEDASTRONAUT_H
