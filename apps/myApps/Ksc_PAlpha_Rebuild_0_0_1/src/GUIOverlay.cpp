#include "GUIOverlay.h"

GUIOverlay::GUIOverlay() : GUI() {
    //ctor
}

GUIOverlay::GUIOverlay(ofVec2f _pos, string _display_text) : GUI(_pos) {
    pos = _pos;
    display_text = _display_text;
    ACTIVE = true;
}

GUIOverlay::~GUIOverlay() {
    //dtor
}

void GUIOverlay::update() {

}

void GUIOverlay::draw() {
    if (ACTIVE) {
        ofPushMatrix();
        ofDrawBitmapStringHighlight(display_text, pos, dark_grey, green);
        ofPopMatrix();
    }
}



