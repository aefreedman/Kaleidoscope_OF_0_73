#include "Planet.h"

Planet::Planet() : Gravitator() {}

Planet::Planet(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {
    habitable = true;
}

Planet::Planet(ofVec2f _pos, int _r, int _gR) : Gravitator(_pos, _r, _gR) {
    habitable = true;}

Planet::~Planet() {
    //dtor
}

void Planet::setup() {

}

void Planet::update() {

}

void Planet::draw() {
    ofSetCircleResolution(64);
    ofFill();
    ofSetColor(255, 255, 255, 255);
    ofCircle(pos, r);

    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    ofCircle(pos, gR);

    ofSetColor(255, 0, 0, 255);
    ofDrawBitmapString(ofToString(m), pos);

}

