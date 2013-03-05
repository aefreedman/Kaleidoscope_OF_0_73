#include "BlackHole.h"

BlackHole::BlackHole()
{
    //ctor
}

BlackHole::BlackHole(ofVec2f _pos, int _r, int _m, int _gR, bool _habitable) : Gravitator(_pos, _r, _m, _gR, _habitable) {}


BlackHole::~BlackHole()
{
    //dtor
}

void BlackHole::setup() {}
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
