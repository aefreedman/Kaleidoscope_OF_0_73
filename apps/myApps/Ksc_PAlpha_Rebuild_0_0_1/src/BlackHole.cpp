#include "BlackHole.h"

BlackHole::BlackHole() : Gravitator()
{
    //ctor
}

BlackHole::BlackHole(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {
    habitable = false;
    type = "blackhole";
    G = 1750;

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
    ofSetColor(60, 0, 90, 255);
    ofCircle(pos, r);

    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    ofCircle(pos, gR);
}
