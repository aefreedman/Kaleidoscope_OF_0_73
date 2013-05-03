#include "GUIFadeOut.h"
#define dt 1.0/60.0

GUIFadeOut::GUIFadeOut() : GUI() {
    //ctor
}

GUIFadeOut::GUIFadeOut(ofVec2f _pos) : GUI(_pos) {
    pos = _pos;
    setup();
}

GUIFadeOut::~GUIFadeOut() {
    //dtor
}

void GUIFadeOut::setup() {
    ACTIVE = false;
    max_timer = 3.0;
    timer = max_timer;
    alpha = 255;
}

void GUIFadeOut::update() {
    if (ACTIVE) {
        timer -= dt;
        alpha = 255 - ((timer / max_timer) * 255);
    }
    if (timer <= 0) {
        ACTIVE = false;
    }
}

void GUIFadeOut::draw() {
    if (ACTIVE) {
    ofPushMatrix();
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, alpha);
    ofRect(pos.x, pos.y, ofGetWidth(), ofGetHeight());
    ofPopMatrix();
    }
}

int GUIFadeOut::getAlpha() {
    return alpha;
}
