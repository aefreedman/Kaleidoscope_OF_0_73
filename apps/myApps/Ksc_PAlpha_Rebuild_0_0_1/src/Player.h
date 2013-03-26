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
#define fps 60
#define screen_width 1280
#define screen_height 720

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
    void detectPlanetCollisions();
    void collisionData(int collision);
    bool detectCollisions();
    void bounce();
    void orientToPlanet(int collision);
    void rotateDirection(bool rotate_left);
    void traversePlanet(bool move_left);
    void calculateGravity(int attractor);
    void jetpack();
    inline ofQuaternion AngularVelocityToSpin(ofQuaternion orientation, ofVec2f angular_v);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);

    std::vector<Gravitator *> *gravitator;
    std::vector<StrandedAstronaut *> *strandedAstronaut;

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
    float maxJump;
    float oxygen;
    float rotation_speed;
    float speed_on_planet;
    float jetpack_power;
    float jump_multiplier;
    float jetpack_o2_use;

    int w;
    int h;
    int r;
    int collision;
    int attractor;

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
    bool GUI;
protected:


private:

    float G;
    bool DEBUG;
    int off_screen_limit;
    ofVec2f display_g;
    ofVec2f display_a;
    ofVec2f display_f;

    ofVec2f planet_pos;
    ofVec2f collision_normal;
    ofVec2f normalized_collision_normal;
    ofVec2f collision_perpendicular;
    float planet_m;
    float planet_r;


};

#endif // PLAYER_H
