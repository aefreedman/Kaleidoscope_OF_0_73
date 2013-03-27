#include "GUI.h"

GUI::GUI() : Shell() {
    //ctor
}

GUI::GUI(ofVec2f _pos) : Shell() {
    pos = _pos;
    //ofColor dark_grey(50, 50, 50);
    //ofColor light_blue(0, 50, 255);
}
GUI::~GUI() {
    //dtor
}

void GUI::update() {}

void GUI::draw() {}
