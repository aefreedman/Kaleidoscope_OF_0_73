#include "testApp.h"
#define dt 1.0/60.0

//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    //currentScreen = &menuScreen;
    currentScreen = &gameScreen;
    gameScreen.setup();

    currentScreen->setup();
    ofEnableAlphaBlending();
    STARTED = false;
    start_timer = 3.0;


}

//--------------------------------------------------------------
void testApp::update(){

    currentScreen->update();

    if (STARTED) {
        start_timer = countdownTimer(start_timer);
    }

    if (start_timer <= 0) {
        //&gameScreen.(*gui).push_back(new GUIFadeIn(&gameScreen.player.pos));
        currentScreen = &gameScreen;
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
                menuScreen.fxEngineLoop.stop();
                menuScreen.fxExplosion.play();
                STARTED = true;
                //currentScreen->setup();
            }
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
