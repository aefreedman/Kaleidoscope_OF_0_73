#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //ofSetFramerate(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);

    nGravitators = 1;
    gravitator = new Gravitator*[nGravitators];
    for (int i = 0; i < nGravitators; i++) {
        gravitator[i] = new Planet(ofVec2f(100, 100), 54, 5, 170);
    }

    planet2 = Sun(ofVec2f(200, 200), 60, 80, 80);
    a = Player(ofVec2f(300,300));


}

//--------------------------------------------------------------
void testApp::update(){
    a.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    for (int i = 0; i < nGravitators; i++) {
        gravitator[i]->draw();
    }

    planet2.draw();
    a.draw();

}

void addGravitator() {

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
