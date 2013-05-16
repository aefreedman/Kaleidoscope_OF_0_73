#include "EndScreen.h"

EndScreen::EndScreen()
{
    setup();
}

EndScreen::~EndScreen()
{
    //dtor
}

void EndScreen::setup() {
    loadResources();
    reset();
}

void EndScreen::loadResources() {
    fadeOut = GUIFadeOut(ofVec2f(0, 0));
    fadeIn = GUIFadeIn(ofVec2f(0, 0));
    image.loadImage("ART/endScreen.png");
}

void EndScreen::reset() {
    TRANSITION_OUT = false;
    LEAVE_SCREEN = false;

    fadeIn.setActive(true);
}

void EndScreen::update() {
    if (LEAVE_SCREEN) {
        return;
    } else {
        if (TRANSITION_OUT) {
            if (!fadeOut.getActive()) {
                fadeOut.setActive(true);
            }
            if (fadeOut.getAlpha() == GUIFadeOut::BLACK) {
                LEAVE_SCREEN = true;
            }
        }
    }
}

void EndScreen::draw() {
    ofPushMatrix();
        ofSetBackgroundColor(ofColor::black);
        ofSetColor(ofColor::white);
        image.draw(ofPoint(0, 0));
    ofPopMatrix();
}

void EndScreen::keyPressed(int key) {
    switch (key) {
        case 32:
            TRANSITION_OUT = true;
            break;
    }
}
