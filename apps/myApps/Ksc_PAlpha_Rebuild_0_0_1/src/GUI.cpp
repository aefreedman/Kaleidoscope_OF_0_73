#include "GUI.h"

GUI::GUI() : Shell() {
    //ctor
    setupColors();
}

GUI::GUI(ofVec2f _pos) : Shell() {
    pos = _pos;
    setupColors();
}
GUI::~GUI() {
    //dtor
}

void GUI::update() {}
void GUI::draw() {}

void GUI::setupColors() {
    ///OfColor blank template
    //color.r           = 0;
    //color.g           = 0;
    //color.b           = 0;
    //color.a           = 255;

    red.r               = 255;
    red.g               = 0;
    red.b               = 0;
    red.a               = 255;

    green.r             = 0;
    green.g             = 255;
    green.b             = 0;
    green.a             = 255;

    blue.r              = 0;
    blue.g              = 0;
    blue.b              = 255;
    blue.a              = 255;

    white.r             = 255;
    white.g             = 255;
    white.b             = 255;
    white.a             = 255;

    black.r             = 0;
    black.g             = 0;
    black.b             = 0;
    black.a             = 255;

    dark_grey.r         = 25;
    dark_grey.g         = 25;
    dark_grey.b         = 25;
    dark_grey.a         = 255;

    light_blue.r        = 0;
    light_blue.g        = 70;
    light_blue.b        = 205;
    light_blue.a        = 255;
}
