#include "Gravitator.h"

Gravitator::Gravitator()
{
    //ctor
}

Gravitator::Gravitator(ofVec2f _pos, int _r, int _m, int _gR) {
    pos = _pos;
    r = _r;
    m = _m;
    gR = _gR;

}

Gravitator::Gravitator(ofVec2f _pos, int _r, int _gR) {
    pos = _pos;
    r = _r;
    gR = _gR;
}

Gravitator::Gravitator(ofVec2f _pos, int _r){
    pos = _pos;
    r = _r;
    gR = 0;
}

void Gravitator::setup() {

}

void Gravitator::update() {

}

void Gravitator::draw() {

}

Gravitator::~Gravitator()
{
    //dtor
}
