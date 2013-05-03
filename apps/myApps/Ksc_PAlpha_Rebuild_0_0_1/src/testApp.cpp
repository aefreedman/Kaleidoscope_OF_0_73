#include "testApp.h"
#define dt 1.0/60.0

//--------------------------------------------------------------
void testApp::setup(){
    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    STARTED                         = false;

    ///------------------------------
    /// YOU CAN CHANGE THESE
    ///------------------------------
    start_timer                     = 9.0;
    timer                           = start_timer;
    currentScreen                   = &menuScreen;
//    currentScreen                 = &gameScreen;
    LOAD_WITH_SOUND                 = true;

    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------
    if (!LOAD_WITH_SOUND) {
        menuScreen.LOAD_WITH_SOUND = false;
        gameScreen.LOAD_WITH_SOUND = false;
    } else {
        menuScreen.LOAD_WITH_SOUND = true;
        gameScreen.LOAD_WITH_SOUND = true;
    }
    gameScreen.setup();
    currentScreen->setup();
}

//--------------------------------------------------------------
void testApp::update(){

    currentScreen->update();

    if (STARTED) {
        timer = countdownTimer(timer);
    }
    if (timer <= 0) {
        currentScreen = &gameScreen;
        gameScreen.ENABLE_EDITOR = false;
        gameScreen.fadeIn.ACTIVE = true;
    }

}

//--------------------------------------------------------------
void testApp::draw(){

    currentScreen->draw();

}

float testApp::countdownTimer(float time) {
    time -= dt;
    return time;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    currentScreen->keyPressed(key);
    switch (key) {
        case 32:
            if (currentScreen == &menuScreen) {
                menuScreen.EXPLODING = true;
                STARTED = true;
                //currentScreen->setup();
            }
        break;
        case OF_KEY_F1:
            gameScreen.ENABLE_EDITOR = true;
            currentScreen = &gameScreen;
            menuScreen.fxEngineLoop.stop();
        break;
    }
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
    currentScreen->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    if (w != 1280 || h != 720) {
        ofSetWindowShape(1280, 720);
    }
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

void testApp::exit() {
    currentScreen->exit();
}
