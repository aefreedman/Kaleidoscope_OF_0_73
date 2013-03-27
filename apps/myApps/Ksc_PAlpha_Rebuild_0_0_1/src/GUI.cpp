#include "GUI.h"

GUI::GUI() : Shell() {
    //ctor
}

GUI::GUI(ofVec2f _pos) : Shell() {
    pos = _pos;
}
GUI::~GUI() {
    //dtor
}

void GUI::update() {}

void GUI::draw() {}
