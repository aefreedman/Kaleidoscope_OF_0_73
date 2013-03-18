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
    void detectPlanetCollisions();
    void orientToPlanet(int collision);
    void calculateGravity(int attractor);
    inline AngularVelocityToSpin(ofQuaternion orientation, ofVec2f angular_v);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);

    ofVec2f pos;
    ofVec2f gravity;
    ofVec2f v;
    ofVec2f a;
    ofVec2f p;
    ofVec2f jp;
    ofVec2f left;
    ofVec2f right;
    ofVec2f jumpDir;
    ofVec2f f;
    ofVec2f dir;
    ofVec2f angular_v
    ofQuaternion orientation;

    float m;
    float rotation;
    float damp;
    float jumpStrength;

    int w;
    int h;
    int maxJump;

    std::vector<Gravitator *> *gravitator;

    bool test;
    bool TEST2;
    bool ON_PLANET;
    bool IN_GRAVITY_WELL;
    bool EXITED_GRAVITY_WELL;
    //bool can_jetpack;
    //bool can_move;
    //bool can_jump;
    //bool has_follower;

    float dt;


protected:


private:
    int collision;
    int attractor;
    float G;
    bool DEBUG;


};

#endif // PLAYER_H
