#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);

    nGravitators = 3;
    for (int i = 0; i < nGravitators; i++) {
        gravitator.push_back(new Planet(ofVec2f(200+50*i, 100+150*i), 54, 5, 200));
    }

    planet2 = Sun(ofVec2f(200, 200), 60, 80, 80);
    a = Player(ofVec2f(300,300), &gravitator);


}

//--------------------------------------------------------------
void testApp::update() {
    a.update();

}

//--------------------------------------------------------------
void testApp::draw() {
    for (int i = 0; i < nGravitators; i++) {
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
    case OF_KEY_LEFT:
        a.dir.set(a.leftDir);
        break;
        //right
    case OF_KEY_RIGHT:
        a.dir.set(a.rightDir);
        break;
    case 32:
        a.chargeJump();
        break;
    }
    /*
    //Temporary movement for player
    float _v = 5.0;
    if (key == 'a' && a.v.x < _v) {
        a.dir.set(a.leftDir);
        //a.v.x += -5.0;
    }
    if (key == 'd' && a.v.x < _v) {
        a.dir.set(a.rightDir);
        //a.v.x += 5.0;
    }
    if (key == 'w' && a.v.y < _v) {
        a.v.y += -5.0;
    }
    if (key == 's' && a.v.x < _v) {
        a.v.y += 5.0;
    } //else a.v.set(0, 0);
    */

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    switch (key) {
    case 356:
        if (ofGetKeyPressed(358)) {
            a.dir.set(a.rightDir);
        } else {
            a.dir.set(0,0);
        }
        break;
    case 358:
        if (ofGetKeyPressed(356)) {
            a.dir.set(a.leftDir);
        } else {
            a.dir.set(0,0);
        }
        break;
    case 32:
        a.jump();
        break;

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
