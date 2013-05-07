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
    ofSetColor(255, 180, 180, 100);
    ofNoFill();
    ofCircle(pos, gR);
    Gravitator::draw();
}
