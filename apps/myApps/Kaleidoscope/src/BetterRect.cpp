#include "BetterRect.h"

BetterRect::BetterRect(ofVec2f _pos, float _w, float _h) : BaseShape(_pos, _w, _h)
{
    //ctor
}

BetterRect::~BetterRect()
{
    //dtor
}

void BetterRect::draw(){
    ofSetColor(0, 200, 20);
    ofRect(pos, w, h);
}
