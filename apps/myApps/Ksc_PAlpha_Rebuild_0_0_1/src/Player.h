#ifndef PLAYER_H
#define PLAYER_H

#include "Astronaut.h"


class Player : public Astronaut {
public:
    Player();
    Player(ofVec2f _pos);
    virtual ~Player();

    void update();
    void draw();
    void move();
    void jump();
    void chargeJump();
    void orient();

    ofVec2f pos;
    ofVec2f v;
    ofVec2f a;
    ofVec2f dir;
    ofVec2f p;
    ofVec2f jp;

    int w;
    int h;
protected:
private:
};

#endif // PLAYER_H
