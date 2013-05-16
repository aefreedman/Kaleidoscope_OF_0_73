#include "GUIFadeIn.h"
#define dt 1.0/60.0

GUIFadeIn::GUIFadeIn() : GUI() {
    //ctor
}

GUIFadeIn::GUIFadeIn(ofVec2f _pos) : GUI(_pos) {
    pos = _pos;
    setup();
}

GUIFadeIn::~GUIFadeIn() {
    //dtor
}

void GUIFadeIn::setup() {
    ACTIVE = false;
    init_timer = 2.0;
    timer = init_timer;
}

void GUIFadeIn::update() {
    if (ACTIVE) {
        timer -= dt;
        alpha = (timer / init_timer) * 255;
    }
    if (timer <= 0) {
        ACTIVE = false;
    }
}

void GUIFadeIn::draw() {
    if (ACTIVE) {
    ofPushMatrix();
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, alpha);
    ofRect(pos.x, pos.y, ofGetWidth(), ofGetHeight());
    ofPopMatrix();
    }
}

void GUIFadeIn::setTimer(float fade_time) {
    init_timer = fade_time;
    timer = init_timer;
}
