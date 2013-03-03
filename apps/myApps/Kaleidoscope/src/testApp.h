#pragma once

#include "ofMain.h"
#include "ofBall.h"
#include "ofGravitySource.h"
#include "Thing.h"
#include "Follower.h"
#include "BaseShape.h"
#include "BetterCircle.h"
#include "BetterRect.h"

class testApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    float pointA;
    float pointB;
    float radius;



private:
    Thing *myThing;
    BetterCircle *myBCirc;
    BetterRect *myBRect;
    ofGravitySource** myGravitySource;
    int nGSource;
    ofBall** myBall;
    int nBalls;
    bool useAccel;
    bool useVel;
    int sampleRate;
    float move;
    float jump;
    //ofVec2f** gpos;
    //ofVec2f ppos;

};
