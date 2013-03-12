#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);

    nGravitators = 1;
    for (int i = 0; i < nGravitators; i++) {
        gravitator.push_back(new Planet(ofVec2f(640, 480), 80, 2000, 300));
    }

    gravitator.push_back(new Planet(ofVec2f(20, 20), 180, 500, 400));
    gravitator.push_back(new Planet(ofVec2f(900, 300), 80, 100, 200));
    //planet2 = Sun(ofVec2f(200, 200), 60, 80, 80);
    a = Player(ofVec2f(300,300), &gravitator);


}

//--------------------------------------------------------------
void testApp::update() {
    a.update();

}

//--------------------------------------------------------------
void testApp::draw() {
    for (int i = 0; i < gravitator.size(); i++) {
        gravitator[i]->draw();
    }

    planet2.draw();
    a.draw();

}

void addGravitator() {

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    switch (key) {
    case 'a':
        cout << "a";
        a.f = a.left;
        break;
    case 'd':
        cout << "d";
        a.f = a.right;
    case 32:
        a.chargeJump();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    switch (key) {
    case 'a':
        cout << "a";
        //a.f -= a.left;
        break;
    case 'd':
        break;
    case 32:
        a.jump();
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    a.pos.set(mouseX, mouseY);
    a.f.set(0, 0);
    a.v.set(0, 0);

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
