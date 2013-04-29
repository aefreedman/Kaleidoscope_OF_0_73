#include "Planet.h"

Planet::Planet() : Gravitator() {}

Planet::Planet(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {
    setup();
}

Planet::Planet(ofVec2f _pos, int _r, int _gR) : Gravitator(_pos, _r, _gR) {
    setup();
}

Planet::~Planet() {
}

void Planet::setup() {
    Gravitator::setup();
    habitable = true;
    type = "planet";
    G = 300;
    anim = planet1;
    ofEnableAlphaBlending(); // turn on alpha blending. important!}
}
void Planet::update() {
    Gravitator::update();

}

void Planet::draw() {
    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    ofSetCircleResolution(64);
    ofCircle(pos, gR);
    Gravitator::draw();
}

