#ifndef STRANDEDASTRONAUT_H
#define STRANDEDASTRONAUT_H

#include "Astronaut.h"
#include "Shell.h"
#include <vector>
static animation_t floating =
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

class StrandedAstronaut : public Astronaut {
public:
    StrandedAstronaut();
    StrandedAstronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut, std::vector<GUI *> *gui);

    virtual ~StrandedAstronaut();
    void update();
    void draw();
    void move();
    void checkState();
    void bounce(int other);

    void detectGravitatorCollisions();
    void collisionData(int collision);
    void orientToPlanet(int collision);
    void calculateGravity(int attractor);
    void displayMessage();
    bool displayMessageTimer();
    string pickMessage();

    void detectPlayerCollisions();
    void followPlayer();
    void getPlayerData(ofVec2f _player_pos);

    bool FOLLOWING_PLAYER;
    bool CAN_TALK;

    string type;
    int id;

    std::vector<Gravitator *> *gravitator;
    std::vector<GUI *> *gui;
    std::vector<StrandedAstronaut *> *strandedAstronaut;

    ofxSpriteSheetRenderer * nautRenderer;

protected:

private:
    int message_display_chance;
    int message_dieroll;
    float message_timer;
    int message_delay;
    ofVec2f player_pos;

    bool DRAW_MESSAGE;

    int sa_collision;


};

#endif // STRANDEDASTRONAUT_H
