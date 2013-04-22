#include "Screen.h"
#define dt 1.0/60.0

Screen::Screen() {
    //ctor
}

Screen::~Screen() {
    //dtor
}

float Screen::countdownTimer(float time) {
    time -= dt;
    return time;
}


//--------------------------------------------------------------
void Screen::keyPressed(int key){

}

//--------------------------------------------------------------
void Screen::keyReleased(int key){

}

//--------------------------------------------------------------
void Screen::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Screen::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Screen::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Screen::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Screen::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Screen::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Screen::dragEvent(ofDragInfo dragInfo){

}
