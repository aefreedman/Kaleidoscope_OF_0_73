#include "ofBall.h"

ofBall::ofBall(ofVec2f _pos, int _dim) {
    pos = _pos;
    dim = _dim;
    velX = ofRandom(-1, 1);
    velY = ofRandom(-1, 1);
}

ofBall::~ofBall() {
    //dtor
}

void ofBall::update() {
    if(pos.x < 0) {
        pos.x = 0;
        velX *= -1;
    } else if(pos.x > ofGetWidth()) {
        pos.x = ofGetWidth();
        velX *= -1;
    }
    if(pos.y < 0) {
        pos.y = 0;
        velY *= -1;
    } else if(pos.y > ofGetHeight()) {
        pos.y = ofGetHeight();
        velY *= -1;

    }
    pos.x += velX;
    pos.y += velY;
}

void ofBall::draw(){
    ofSetColor(120, 120, 120);
    ofCircle(pos.x, pos.y, dim);
}
