#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Astronaut.h"
#include "Gravitator.h"
#include <iostream>


class Player : public Astronaut {
public:
    Player();
    Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator);
    virtual ~Player();

    void setup();
    void update();
    void draw();
    void move();
    void jump();
    void chargeJump();
    void orientToPlanet(ofVec2f cOfGrav, float gR, float r, bool habitable, int mBody);
    void getNearPlanet();
    void gravity();
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);

    ofVec2f pos;
    ofVec2f v;
    ofVec2f a;
    ofVec2f p;
    ofVec2f jp;
    ofVec2f left;
    ofVec2f right;
    ofVec2f jumpDir;
    ofVec2f f;

    float m;
    float rotation;
    float damp;
    float jumpStrength;

    int w;
    int h;
    int maxJump;

    std::vector<Gravitator *> *gravitator;
protected:
private:
    bool nearPlanet;
    bool touchingPlanet;
    float G;
};

#endif // PLAYER_H
