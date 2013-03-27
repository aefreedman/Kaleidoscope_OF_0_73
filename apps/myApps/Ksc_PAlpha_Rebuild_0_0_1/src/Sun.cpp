#include "Sun.h"

Sun::Sun() : Gravitator()
{
    //ctor
}

Sun::Sun(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {
    type = "sun";

}

Sun::~Sun()
{
    //dtor
}

void Sun::setup() {
    habitable = false;
}
void Sun::update() {}
void Sun::draw() {
    ofSetCircleResolution(64);
    ofFill();
    ofSetColor(255, 255, 0, 255);
    ofCircle(pos, r);

    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    ofCircle(pos, gR);
}
