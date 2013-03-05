#include "Astronaut.h"

Astronaut::Astronaut() {
    //ctor
}

Astronaut::Astronaut(ofVec2f _pos) {
    pos = _pos;
}

Astronaut::~Astronaut() {
    //dtor
}

void Astronaut::setup() {
    w = 5;
    h = 7;
    v.set(0.001, -0.001);
}

void Astronaut::update() {
    pos += v;
}

void Astronaut::draw() {
    ofPushMatrix();
    ofColor astronaut(0, 180, 60);
    ofSetColor(astronaut);
    ofFill();
    ofRect(pos, w, h);
    ofPopMatrix();
}
void Astronaut::move() {

}
