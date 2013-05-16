#include "Gravitator.h"

Gravitator::Gravitator() : GameObject() {
    //ctor
}

Gravitator::Gravitator(ofVec2f _pos, int _r, int _m, int _gR) : GameObject() {
    pos = _pos;
    r = _r;
    m = _m;
    gR = _gR;
}

Gravitator::Gravitator(ofVec2f _pos, int _r, int _gR) : GameObject() {
    pos = _pos;
    r = _r;
    gR = _gR;
}

Gravitator::Gravitator(ofVec2f _pos, int _r) {
    pos = _pos;
    r = _r;
}

void Gravitator::setup() {

    ptclCount = r/4;
    ofVec2f up;
    up.set(0,-1);
    for (int i = 0; i<ptclCount; i++){
        ofVec2f startVector;
        startVector = up.getRotated(int(ofRandom(360)),pos);
        startVector.normalize();
        ptcl.push_back(pos + (startVector * (ofRandom(-gR,gR))));
    }

}

void Gravitator::update() {
    for (int i = 0; i<ptclCount; i++){
        ofVec2f ptclNorm;
        ptclNorm = ptcl[i] - pos;
        ptclNorm.normalize();
        ptcl[i] -= ptclNorm * G/500;

        if (pos.distance(ptcl[i])<1){
        ofVec2f up;
        up.set(0,-1);
        ofVec2f startVector;
        startVector = up.getRotated(int(ofRandom(360)),pos);
        startVector.normalize();
        ptcl[i] = pos + (startVector * gR * int((ofRandom(-2,2))));
        }


    }

}

void Gravitator::draw() {

    for (int i = 0; i < ptclCount; i++){
        ofFill();
        if (pos.distance(ptcl[i])>gR/2){
        ofSetColor(255,255,255,180 - (180*(pos.distance(ptcl[i])/gR)));
        } else {
        ofSetColor(255,255,255,0 + (180*(pos.distance(ptcl[i])/gR)));
        }
        ofRect(ptcl[i],4,4);
    }

}

void Gravitator::drawPath() {}

Gravitator::~Gravitator() {
    //dtor
}
