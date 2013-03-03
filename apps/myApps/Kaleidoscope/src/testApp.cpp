#include "testApp.h"
#include <iostream>

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);

    sampleRate = 5;
    useAccel = false;
    useVel = true;
    ofVec2f center;
    center.set(ofGetWidth()/2, ofGetHeight()/2);
    move = 1;
    jump = move * 10;

    nBalls = 80;
    myBall = new ofBall*[nBalls];
    for(int i = 0; i < nBalls; i++) {
        ofVec2f pos((20+(100+i)), (20+(100+i)));
        int dim = 5 + (i/10*ofRandom(1, 3));
        //pos.rotate(ofRandom(0,360));
        myBall[i] = new ofBall(pos, dim, i);
    }

    ofVec2f pos = center;
    int r = 10;
    ofVec2f vel = ofVec2f(0, 0);
    ofVec2f accel = ofVec2f(0, 0);
    float damp = 0.985;
    ofVec2f g = ofVec2f(0, .5);
    myThing = new Thing(pos, r, vel, accel, damp, g);

    nGSource = 20;
    myGravitySource = new ofGravitySource*[nGSource];
    for(int i = 0; i < nGSource; i++) {
        myGravitySource[i] = new ofGravitySource(center, ofVec2f(ofRandom(-1,1), ofRandom(-1,1)), 4, 10, ofRandom(60, 100));
    }

    myBCirc = new BetterCircle(ofVec2f(300, 700), 30);
    myBRect = new BetterRect(ofVec2f(400, 600), 20, 10);

}

//--------------------------------------------------------------
void testApp::update() {
        myThing->xG = myThing->g;
        myThing->damp = .985;
        move = 1;
        jump = move * 10;
    for(int i = 0; i < nGSource; i++) {
        myGravitySource[i]->update();
        float distance [nGSource];
        distance[i] = myThing->pos.distance(myGravitySource[i]->pos);
        if (distance[i] >= myGravitySource[i]->gRange) {
        }
        if (distance[i] <= myGravitySource[i]->gRange) {
            myThing->xG.set(0,0);
            myThing->damp = 0.95;
            move = 2;
            jump = move;
        }
    }
    for(int i = 0; i < nBalls; i++) {
        myBall[i]->update();
    }
    myThing->update();
    myBCirc->update();

    string info = "";
    info += "Pos: " + ofToString(myThing->pos) + " * Vel: " + ofToString(myThing->vel) + " * aAccel: " + ofToString(myThing->accel) + "\n";
    //cout << info;
}



//--------------------------------------------------------------
void testApp::draw() {

    for(int i = 0; i < nBalls; i++) {
        myBall[i]->draw();
    }
    for(int i = 0; i < nGSource; i++) {
        myGravitySource[i]->draw();
    }

    //myBCirc->draw();
    //myBRect->draw();
    myThing->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    if (useAccel) {
        float move = 100;
        if (key == 'w') {
            myThing->accel.y -= move;
        }
        if (key == 'a') {
            myThing->accel.x -= move;
        }
        if (key == 's') {
            myThing->accel.y += move;
        }
        if (key == 'd') {
            myThing->accel.x += move;
        }
    }
    if (useVel) {
        if (key == 'w') {
            myThing->vel.y -= jump;
        }
        if (key == 'a') {
            myThing->vel.x -= move;
        }
        if (key == 's') {
            myThing->vel.y += move;
        }
        if (key == 'd') {
            myThing->vel.x += move;
        }
    }

    ofSetHexColor(0x444342);
    //ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    //myThing->accel.set(0, 0);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
    //myThing->pos.set(mouseX, mouseY);


}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    //myThing->rP.set(mouseX, mouseY);


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
