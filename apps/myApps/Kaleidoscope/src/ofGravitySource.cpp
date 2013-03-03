#include "ofGravitySource.h"

ofGravitySource::ofGravitySource(ofVec2f _pos, ofVec2f _vel, float _r, float _gPwr, int _gRange)
{
    pos = _pos;
    vel = _vel;
    r = _r;
    gPwr = _gPwr;
    gRange = _gRange;
}

ofGravitySource::~ofGravitySource()
{
    //dtor
}

void ofGravitySource::update() {
    //vel = damp * (vel + accel);
    pos = pos + vel;

    if(pos.x < r) {
        pos.x = r;
        vel.x *= -1;
    } else if(pos.x > ofGetWidth() - r) {
        pos.x = ofGetWidth() - r;
        vel.x *= -1;
    }
    if(pos.y < r) {
        pos.y = r;
        vel.y *= -1;
    } else if(pos.y > ofGetHeight() - r) {
        pos.y = ofGetHeight() - r;
        vel.y *= -1;
    }

}

void ofGravitySource::draw() {
    ofPushMatrix();
    ofFill();
    //ofEnableAlphaBlending();
    ofSetColor(0, 255, 80, 100);
    ofCircle(pos, r);
    ofNoFill();
    ofSetColor(0, 0, 255);
    ofCircle(pos, gRange);
    ofPopMatrix();
}
