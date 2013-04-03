#ifndef PLAYER_H
#define PLAYER_H
#define nl '\n'
#define screen_width 1280
#define screen_height 720

#include <vector>
#include <iostream>
#include "ofMain.h"
#include "Gravitator.h"
#include "Astronaut.h"
#include "StrandedAstronaut.h"
#include "Shell.h"


class Player : public Astronaut {
public:
    Player();
    Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut, std::vector<GUI *> *gui);
    virtual ~Player();

    void setup();
    void update();
    void draw();
    void drawGUI();
    void drawDebugGUI();
    void move();
    void jump();
    void chargeJump();
    void detectAstronautCollisions();
    void releaseAstronaut(int i);
    void releaseAllAstronauts();
    void detectGravitatorCollisions();
    void collisionData(int collision);
    bool detectCollisions();
    bool checkOffScreen();
    void checkState();
    void die();
    void orientToPlanet(int collision);
    void rotateDirection(bool rotate_left);
    void traversePlanet(bool move_left);
    void calculateGravity(int attractor);
    void jetpack(bool JETPACK_FORWARD);
    inline ofQuaternion AngularVelocityToSpin(ofQuaternion orientation, ofVec2f angular_v);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    void drawGUIOverlay(ofVec2f _pos, string text);
    void displayMessage(ofVec2f _pos, string text);


    std::vector<Gravitator *> *gravitator;
    std::vector<StrandedAstronaut *> *strandedAstronaut;
    std::vector<GUI *> *gui;

    ofVec3f camera_pos;
    ofVec3f camera_target;
    string camera_move_direction;
    float camera_timer;

    float jumpStrength;
    float rotation_speed;
    float speed_on_planet;
    float jetpack_power;
    float jump_multiplier;
    float jetpack_o2_use;

    bool CAN_JETPACK;
    bool CAN_LAND_ON_PLANET;
    bool OFF_SCREEN_RESET;
    bool DEBUG_GUI;
    bool TRAVERSING_PLANET;
    bool OFF_SCREEN;
    bool GOD_MODE;
    bool LEAVING_PLANET;
protected:


private:
    int astronaut_pickup_range;
    int astronaut_drop_range;
    //float G;
    bool DEBUG;
    int off_screen_limit;
    ofVec2f display_g;
    ofVec2f display_a;
    ofVec2f display_f;

    float jump_strength_1;
    float jump_strength_2;
    float jump_strength_3;
    float jump_timer;
    int jetpack_count;
    int max_jetpack_count;
    float max_oxygen;

    /// TODO (Aaron#1#): discrete jump strength levels
    /// TODO (Aaron#1#): Release astronauts into the sun


};

#endif // PLAYER_H
