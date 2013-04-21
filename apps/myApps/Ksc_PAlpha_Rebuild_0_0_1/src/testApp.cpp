#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    currentScreen = &menuScreen;

    currentScreen->setup();
    ofEnableAlphaBlending();


}

//--------------------------------------------------------------
void testApp::update(){

    currentScreen->update();

}

//--------------------------------------------------------------
void testApp::draw(){

    currentScreen->draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch (key) {
        case OF_KEY_RETURN:
            if (currentScreen == &menuScreen) {
                currentScreen = &gameScreen;
                currentScreen->setup();
            }
        break;
    }

    currentScreen->keyPressed(key);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

    currentScreen->keyReleased(key);

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    currentScreen->mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    currentScreen->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    currentScreen->mousePressed(x, y, button);

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
