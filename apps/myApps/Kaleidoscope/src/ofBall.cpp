#include "ofBall.h"

ofBall::ofBall(ofVec2f _pos, int _dim, int _id) {
    pos = _pos;
    dim = _dim;
    float s = 1.2;
    vel = ofVec2f(ofRandom(-s, s), ofRandom(-s, s));
    id = _id;
}

ofBall::~ofBall() {
    //dtor
}

void ofBall::update() {
    if(pos.x < 0) {
        pos.x = 0;
        vel.x *= -1;
    } else if(pos.x > ofGetWidth()) {
        pos.x = ofGetWidth();
        vel.x *= -1;
    }
    if(pos.y < 0) {
        pos.y = 0;
        vel.y *= -1;
    } else if(pos.y > ofGetHeight()) {
        pos.y = ofGetHeight();
        vel.y *= -1;

    }
    pos += vel;
}

void ofBall::draw(){

    ofPushMatrix();
    ofNoFill();
    ofSetColor(200, 120, 120);
    ofCircle(pos, dim);
    ofPopMatrix();

    ofPushMatrix();
    ofFill();
    ofSetColor(0, 0, 0, 205);
    ofCircle(pos, dim);
    ofPopMatrix();

    ofPushMatrix();
    ofNoFill();
    ofSetColor(200, 120, 120);
    ofCircle(pos, 5);
    ofPopMatrix();

}
