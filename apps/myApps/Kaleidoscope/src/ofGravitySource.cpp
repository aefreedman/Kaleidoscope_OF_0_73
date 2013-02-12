#include "ofGravitySource.h"

ofGravitySource::ofGravitySource(ofVec2f _pos, float _dim, float _gPwr)
{
    pos = _pos;
    dim = _dim;
    gPwr = _gPwr;
}

ofGravitySource::~ofGravitySource()
{
    //dtor
}

void ofGravitySource::update() {

}

void ofGravitySource::draw() {
    ofSetColor(0, 0, 0);
    ofCircle(pos.x, pos.y, dim);
}
