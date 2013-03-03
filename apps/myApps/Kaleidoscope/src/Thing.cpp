#include "Thing.h"

Thing::Thing(ofVec2f _pos, int _r, ofVec2f _vel, ofVec2f _accel, float _damp, ofVec2f _g) {
    pos = _pos;
    r = _r;
    accel = _accel;
    vel = _vel;
    damp = _damp;
    g = _g;
}
Thing::Thing(ofVec2f _pos, int _r) {
    pos = _pos;
    r = _r;
}


Thing::~Thing() {
    //dtor
}

void Thing::setup() {
    xG = g;
    m = 1;
    k = -0.05;
    f.set(0, 0);
    rP = pos;
}

void Thing::update() {

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

    dir = vel.getNormalized();

    //f = k * (pos - rP);
    accel = f / m;
    accel = xG;
    vel = damp * (vel + accel);
    pos = pos + vel;
    //pos.rotate(5, pos);
}

void Thing::draw() {
    ofPushMatrix();
    ofSetColor(255);
    ofNoFill();
    ofCircle(pos, r);
    ofCircle(pos.x, pos.y + 20, r/4);
    ofPopMatrix();

}
