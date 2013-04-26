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
    start_timer                     = 3.0;
    timer                           = start_timer;
//    currentScreen                   = &menuScreen;
    currentScreen                 = &gameScreen;
    LOAD_WITH_SOUND                 = false;

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
        menuScreen.fxEngineLoop.stop();
        currentScreen = &gameScreen;
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
                menuScreen.fxExplosion.play();
                STARTED = true;
                menuScreen.guiFadeOut.max_timer = start_timer + 1;
                menuScreen.guiFadeOut.timer = start_timer + 1;
                //currentScreen->setup();
            }
        break;
        case 'c':
            gameScreen.CONTINUOUS_CAMERA = !gameScreen.CONTINUOUS_CAMERA;
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
