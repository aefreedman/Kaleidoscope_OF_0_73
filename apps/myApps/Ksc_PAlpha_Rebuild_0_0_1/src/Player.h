#ifndef PLAYER_H
#define PLAYER_H
#define nl '\n'
#define screen_width 1280
#define screen_height 720

#include <vector>
#include <iostream>
#include "ofMain.h"
#include "Gravitator.h"
#include "Planet.h"
#include "Sun.h"
#include "BlackHole.h"
#include "Astronaut.h"
#include "Player.h"
#include "StrandedAstronaut.h"
#include "Decor.h"
#include "Shell.h"
#include "Solid.h"
#include "Nonsolid.h"

class Player : public Astronaut {
public:
    Player();
    Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut);
    virtual ~Player();

    void setup();
    void update();
    void draw();
    void drawGUI();
    void move();
    void jump();
    void chargeJump();
    void detectAstronautCollisions();
    void detectGravitatorCollisions();
    void collisionData(int collision);
    bool detectCollisions();
    void orientToPlanet(int collision);
    void rotateDirection(bool rotate_left);
    void traversePlanet(bool move_left);
    void calculateGravity(int attractor);
    void jetpack(bool JETPACK_FORWARD);
    inline ofQuaternion AngularVelocityToSpin(ofQuaternion orientation, ofVec2f angular_v);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);

    std::vector<Gravitator *> *gravitator;
    std::vector<StrandedAstronaut *> *strandedAstronaut;

    float jumpStrength;
    float maxJump;
    float rotation_speed;
    float speed_on_planet;
    float jetpack_power;
    float jump_multiplier;
    float jetpack_o2_use;

    bool CAN_JETPACK;
    bool ABSOLUTE_IMPULSE;
    bool ROTATIONAL_IMPULSE;
    bool CAN_LAND_ON_PLANET;
    bool OFF_SCREEN_RESET;
    bool GUI;
    bool TRAVERSING_PLANET;
protected:


private:
    int astronaut_pickup_range;
    //float G;
    bool DEBUG;
    int off_screen_limit;
    ofVec2f display_g;
    ofVec2f display_a;
    ofVec2f display_f;
/*
    ofVec2f planet_pos;
    ofVec2f collision_normal;
    ofVec2f normalized_collision_normal;
    ofVec2f collision_perpendicular;
    float planet_m;
    float planet_r;
*/

};

#endif // PLAYER_H
