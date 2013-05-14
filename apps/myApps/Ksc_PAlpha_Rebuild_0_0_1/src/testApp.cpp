#include "testApp.h"
#define dt 1.0/60.0

//--------------------------------------------------------------
void testApp::setup() {
    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();

    ///------------------------------
    /// YOU CAN CHANGE THESE
    ///------------------------------
    currentScreen                   = &menuScreen;
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
    setupAllScreens();
}
//--------------------------------------------------------------
void testApp::update() {

    currentScreen->update();

    if (currentScreen == &menuScreen && menuScreen.flashOpacity >= 255) {
        menuScreen.fxEngineLoop.stop();
        currentScreen = &introScreen;
        menuScreen.reset();
    }
    if (currentScreen == &introScreen && introScreen.fadeOutOpacity >= 255) {
        currentScreen = &gameScreen;
        introScreen.reset();
        gameScreen.ENABLE_EDITOR = false;
        gameScreen.fadeIn.setActive(true);
    }
    if (gameScreen.isGameOver() && currentScreen == &gameScreen) {
        currentScreen = &endScreen;
        endScreen.fadeIn.setActive(true);
        gameScreen.exportSessionData();
        resetAllScreens();
    }
    if (endScreen.GetLeaveScreen()) {
        currentScreen = &menuScreen;
        endScreen.reset();
    }
}

void testApp::setupAllScreens() {
    menuScreen.setup();
    endScreen.setup();
    gameScreen.setup();
    introScreen.setup();
}
void testApp::resetAllScreens() {
    menuScreen.reset();
    endScreen.reset();
    gameScreen.setLevel(1);
    gameScreen.reset();
    introScreen.reset();
}

//--------------------------------------------------------------
void testApp::draw() {

    currentScreen->draw();

}

float testApp::countdownTimer(float time) {
    time -= dt;
    return time;
}

void testApp::deleteSaves() {
    struct dirent *next_file;
    DIR *dir;

    char filepath[256];

    dir = opendir("data/levels/saves");

    while ( next_file = readdir(dir) ) {
        sprintf(filepath, "%s/%s", "data/levels/saves", next_file->d_name);
        remove(filepath);
    }
    return;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    currentScreen->keyPressed(key);
    switch (key) {
    case 32:
        if (currentScreen == &menuScreen) {
            deleteSaves();
            menuScreen.EXPLODING = true;
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
void testApp::keyReleased(int key) {
    currentScreen->keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
    currentScreen->mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
    currentScreen->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    currentScreen->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
    currentScreen->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
    if (w != 1280 || h != 720) {
        ofSetWindowShape(1280, 720);
    }
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}

void testApp::exit() {
    gameScreen.exit();
}
