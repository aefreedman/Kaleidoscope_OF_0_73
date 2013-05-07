#ifndef GRAVITATOR_H
#define GRAVITATOR_H

#include "GameObject.h"
#include "ofxSpriteSheetRenderer.h"

static animation_t blackHole =
{	0,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	1,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

static animation_t planet1 =
{	1,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	1,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

static animation_t atmosphere =
{	2,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	1,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

static animation_t comet =
{	4,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	1,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

static animation_t sun =
{	5,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	1,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

class Gravitator : public GameObject {
public:
    Gravitator();
    Gravitator(ofVec2f _pos, int _r, int _m, int _gR);
    Gravitator(ofVec2f _pos, int _r, int _gR);
    Gravitator(ofVec2f _pos, int _r);
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual ~Gravitator();
    virtual void drawPath();

    void spawnParticle();

    vector <ofPoint> ptcl;

    ofVec2f pos;
    float G;
    int ptclCount;
    int r;
    int gR;
    int m;
    float p;
    bool habitable;
    string type;
    animation_t anim;
    animation_t anim2;


    vector <ofVec2f> pathPoints;


protected:
private:
};

#endif // GRAVITATOR_H
