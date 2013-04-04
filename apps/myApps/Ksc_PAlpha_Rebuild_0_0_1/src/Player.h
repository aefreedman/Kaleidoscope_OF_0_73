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

static animation_t walking =
{	0,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	8,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

static animation_t jetpack =
{	21,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	5,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};


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

    ofxSpriteSheetRenderer * p1Renderer;


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
    bool DEBUG_GUI;
    bool TRAVERSING_PLANET;
    bool OFF_SCREEN;
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
