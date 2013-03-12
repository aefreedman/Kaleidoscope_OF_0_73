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
    void orientToPlanet(ofVec2f cOfGrav, float gR, float r, bool habitable);
    void getNearPlanet();
    void gravity();
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);

    ofVec2f pos;
    ofVec2f v;
    ofVec2f a;
    ofVec2f dir;
    ofVec2f p;
    ofVec2f jp;
    ofVec2f leftDir;
    ofVec2f rightDir;
    ofVec2f jumpDir;

    float rotation;
    float damp;
    float jumpStrength;

    int w;
    int h;
    int closestPlanet;
    int maxJump;

    std::vector<Gravitator *> *gravitator;
protected:
private:
    bool nearPlanet;
    bool touchingPlanet;
    ofVec2f momentum;
    ofVec2f f;

};

#endif // PLAYER_H
