#include "BlackHole.h"

BlackHole::BlackHole() : Gravitator()
{
    //ctor
}

BlackHole::BlackHole(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {
    habitable = false;
    type = "blackhole";
    G = 1000;
    anim = blackHole;
    Gravitator::setup();
}


BlackHole::~BlackHole()
{
    //dtor
}

void BlackHole::setup() {
    habitable = false;
    anim = blackHole;
}
void BlackHole::update() {
    Gravitator::update();
}
void BlackHole::draw() {
    /*ofSetCircleResolution(64);
    ofFill();
    ofSetColor(60, 0, 90, 255);
    ofCircle(pos, r);*/

   /*ofSetColor(143, 3, 112, 255);
    ofSetLineWidth(2);
    ofSetColor(255, 170, 255, 100);
    ofNoFill();
    ofCircle(pos, gR);*/

    Gravitator::draw();
}
