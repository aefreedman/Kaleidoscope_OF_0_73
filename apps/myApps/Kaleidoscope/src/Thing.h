#ifndef THING_H
#define THING_H

#include "ofMain.h"


class Thing {
public:
    void setup();
    void update();
    void draw();
    Thing(ofVec2f pos, int r, ofVec2f vel, ofVec2f accel, float damp, ofVec2f g);
    Thing(ofVec2f pos, int r);
    virtual ~Thing();
    ofVec2f pos;
    int r;
    ofVec2f vel;
    ofVec2f accel;
    float damp;
    ofVec2f oldPos;
    ofVec2f g;
    ofVec2f xG;
    ofVec2f dir;
    ofVec2f f;
    float m;
    ofVec2f rP;
    float k;



protected:
private:

};

#endif // THING_H
