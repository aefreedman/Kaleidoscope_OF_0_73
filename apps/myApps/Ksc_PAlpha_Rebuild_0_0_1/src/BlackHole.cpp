#include "BlackHole.h"

BlackHole::BlackHole() : Gravitator()
{
    //ctor
}

BlackHole::BlackHole(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {

}


BlackHole::~BlackHole()
{
    //dtor
}

void BlackHole::setup() {
    habitable = false;
}
void BlackHole::update() {}
void BlackHole::draw() {
    ofSetCircleResolution(64);
    ofFill();
    ofSetColor(255, 0, 255, 255);
    ofCircle(pos, r);

    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    ofCircle(pos, gR);
}
