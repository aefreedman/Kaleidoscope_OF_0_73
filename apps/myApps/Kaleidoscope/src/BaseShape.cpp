#include "BaseShape.h"

BaseShape::BaseShape(ofVec2f _pos, ofVec2f _vel, float _damp)
{
    pos = _pos;
    vel = _vel;
    damp = _damp;
}

BaseShape::BaseShape(ofVec2f _pos, int _r) {
    pos = _pos;
    r = _r;
}

BaseShape::BaseShape(ofVec2f _pos, float _w, float _h) {
    pos = _pos;
    h = _h;
    w = _w;
}

BaseShape::~BaseShape()
{
    //dtor
}

void BaseShape::update() {
    vel = damp * (vel);
    pos = pos + vel;
}

void BaseShape::draw() {

}
