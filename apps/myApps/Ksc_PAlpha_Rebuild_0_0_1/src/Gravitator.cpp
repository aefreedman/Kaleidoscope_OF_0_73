#include "Gravitator.h"

Gravitator::Gravitator()
{
    //ctor
}

Gravitator::Gravitator(ofVec2f _pos, int _r, int _m, int _gR, bool _habitable) {
    pos = _pos;
    r = _r;
    m = _m;
    gR = _gR;
    habitable = _habitable;

}

Gravitator::Gravitator(ofVec2f _pos, int _r, int _gR) {
    pos = _pos;
    r = _r;
    gR = _gR;
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
