#include "MenuScreen.h"

MenuScreen::MenuScreen() : Screen() {
    //ctor
}

MenuScreen::~MenuScreen() {
    //dtor
}

void MenuScreen::setup() {

}

void MenuScreen::update() {

}

void MenuScreen::draw() {
    ofSetColor(230, 124, 212);
    ofDrawBitmapString("HAI GAIZ DIS IZ MENU SCREEN", ofGetWidth() / 2, ofGetHeight() / 2);
}


//--------------------------------------------------------------
void MenuScreen::keyPressed(int key){

}

//--------------------------------------------------------------
void MenuScreen::keyReleased(int key){

}

//--------------------------------------------------------------
void MenuScreen::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void MenuScreen::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void MenuScreen::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void MenuScreen::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void MenuScreen::windowResized(int w, int h){

}

//--------------------------------------------------------------
void MenuScreen::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MenuScreen::dragEvent(ofDragInfo dragInfo){

}

