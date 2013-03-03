#include "BetterCircle.h"

BetterCircle::BetterCircle(ofVec2f _pos, int _r) : BaseShape(_pos, _r) {

}

void BetterCircle::draw() {
    ofSetColor(220, 0, 20);
    ofCircle(pos, r);

}
