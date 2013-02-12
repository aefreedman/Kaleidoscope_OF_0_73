#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

    ofSetVerticalSync(true);

    box2d.init();
    box2d.setGravity(0, 1.0f);
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    box2d.createBounds();

    defRadius = 20;

}

//--------------------------------------------------------------
void testApp::update() {
    box2d.update();

    for(int i = 0; i < circles.size(); i++) {
        if (circles[i].getPosition().y < ofGetHeight() / 2) {
        //circles[i].increaseGravity(0.1f);
        //circles[i].addImpulseForce(circles[i].getPosition(), ofVec2f(0, -1));
        }
    }

}

//--------------------------------------------------------------
void testApp::draw() {
    ofSetColor(0, 0, 0);
    ofRect(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2 + 5);

    for(int i = 0; i < circles.size(); i++) {
        ofFill();
        ofSetColor(200, 0, 0);
        if (circles[i].getPosition().y < ofGetHeight() / 2) {
        ofSetColor(0, 200, 0);
        }
        circles[i].draw();
    }

    box2d.drawGround();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    if(key == 'c') {
       float r = defRadius;
       ofxBox2dCircle circle;
       circle.setPhysics(10, 0.5, 0.2);
       circle.setup(box2d.getWorld(), mouseX, mouseY, r, 1.0f, 0.1f);
       circles.push_back(circle);
       }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

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
