#ifndef PLAYER_H
#define PLAYER_H
#define nl '\n'
#define screen_width 1280
#define screen_height 720

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
    bool detectCollisions();
    void bounce();
    void orientToPlanet(int collision);
    void calculateGravity(int attractor);
    inline ofQuaternion AngularVelocityToSpin(ofQuaternion orientation, ofVec2f angular_v);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);

    ofVec2f pos;
    ofVec2f starting_pos;
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
    ofVec2f angular_v;
    ofQuaternion orientation;

    float m;
    float rotation;
    float damp;
    float jumpStrength;
    float restitution;

    int w;
    int h;
    int r;
    int maxJump;
    int oxygen;

    std::vector<Gravitator *> *gravitator;

    bool ON_PLANET;
    bool IN_GRAVITY_WELL;
    bool EXITED_GRAVITY_WELL;
    bool CAN_JETPACK;
    bool ABSOLUTE_IMPULSE;
    bool ROTATIONAL_IMPULSE;
    bool ORIENT_TO_PLANET;
    bool USING_GRAVITY;
    bool CAN_LAND_ON_PLANET;
    bool OFF_SCREEN_RESET;
    bool SIMPLE_GRAVITY;

protected:


private:
    int collision;
    int attractor;
    float G;
    bool DEBUG;
    int off_screen_limit;
    ofVec2f display_g;
    ofVec2f display_a;
    ofVec2f display_f;


};

#endif // PLAYER_H
