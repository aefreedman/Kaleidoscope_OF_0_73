#include "Sun.h"

Sun::Sun() : Gravitator() {
    //ctor
}

Sun::Sun(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {
    type = "sun";
    pos = _pos;
    r = _r;
    m = _m;
    gR = _gR;
    G = 500;
    anim = sun;
    Gravitator::setup();

}

Sun::~Sun() {
    //dtor
}

void Sun::setup() {
    habitable = false;
}

void Sun::update() {
    Gravitator::update();

}
void Sun::draw() {
    ofSetCircleResolution(64);
    ofSetColor(255, 33, 102, 20);
    ofSetCircleResolution(int(ofRandom(20,30)));
    ofCircle(pos, gR);
//    ofSetColor(255, 120, 102, 15);
//    ofSetCircleResolution(int(ofRandom(6,12)));
//    ofCircle(pos, r + 10);
    Gravitator::draw();
}
