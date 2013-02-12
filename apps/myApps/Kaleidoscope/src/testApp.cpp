#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofBackground(50, 50, 50);

	//myBall = new ofBall(ofRandom(300, 400), ofRandom(200, 300), ofRandom(10, 40));
	nBalls = 5;
        myBall = new ofBall*[nBalls];
    for(int i = 0; i < nBalls; i++){
        ofVec2f pos((20+(100*i)), (20+(100*i)));
        int dim = 10+(i*10);
        //pos.rotate(ofRandom(0,360));
        myBall[i] = new ofBall(pos, dim);
    }

    myGravitySource = new ofGravitySource(ofVec2f((ofGetWidth() /2), (ofGetHeight() /2)), 50, 10);
}

//--------------------------------------------------------------
void testApp::update() {
    pointA += .1;
    for(int i = 0; i < nBalls; i++){
        myBall[i]->update();
    }
}

//--------------------------------------------------------------
void testApp::draw() {
    for(int i = 0; i < nBalls; i++){
        myBall[i]->draw();
    }
    myGravitySource->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
