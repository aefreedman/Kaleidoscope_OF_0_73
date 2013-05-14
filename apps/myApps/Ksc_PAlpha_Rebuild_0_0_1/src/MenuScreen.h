#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"
#include "ofxSpriteSheetRenderer.h"
#include "GUIFadeOut.h"
#include "GUIFadeIn.h"
#include "StrandedAstronaut.h"

static animation_t ship =
{	0,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	4,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

static animation_t explosion =
{	0,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	12,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	35,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};


static animation_t title =
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

class MenuScreen : public Screen {
public:
    MenuScreen();
    virtual ~MenuScreen();

    void setup();
    void update();
    void draw();
    void reset();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofImage background;
    ofImage title;
    ofxSpriteSheetRenderer * menuRenderer;
    ofxSpriteSheetRenderer * splosionRenderer;
    ofxSpriteSheetRenderer * nautRenderer;
    animation_t anim;
    ofTrueTypeFont font;

    int shakeCounter;
    GUIFadeOut guiFadeOut;

    bool EXPLODING;
    bool FLASHING;
    bool BROKEN;

    int flashOpacity;
    int flashFadeRate;
    ofPoint splosion;
    int splosionTimer;
    bool MOVED;

    ofVec3f farStars[30];
    ofVec3f nearStars[30];

    vector <StrandedAstronaut> nauts;

    ofPoint shipPos;
    ofSoundPlayer fxEngineLoop;
    ofSoundPlayer fxExplosion;

    ofVec3f piece1;
    ofVec3f piece2;
    ofVec3f piece3;
    ofVec3f piece4;
    ofVec3f piece5;
    ofVec3f piece6;
    ofVec3f piece7;

    ofImage shipPiece1;
    ofImage shipPiece2;
    ofImage shipPiece3;
    ofImage shipPiece4;
    ofImage shipPiece5;
    ofImage shipPiece6;
    ofImage shipPiece7;

protected:
private:
    ofSoundPlayer fxSmallExplosion;
    ofSoundPlayer fxEngineAmbient;

    GUIFadeIn fadeIn;
    void loadResources();
};

#endif // MENUSCREEN_H
