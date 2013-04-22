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
    G = 200;
    anim = sun;

}

Sun::~Sun() {
    //dtor
}

void Sun::setup() {
    habitable = false;
}

void Sun::update() {

}
void Sun::draw() {
    ofSetCircleResolution(64);
    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    ofCircle(pos, gR);
}
