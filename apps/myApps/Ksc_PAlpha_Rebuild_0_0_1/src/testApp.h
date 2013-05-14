#pragma once
#include "ofMain.h"
#include "Screen.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "IntroScreen.h"
#include "EndScreen.h"
#include <stdio.h>
#include <dirent.h>

class testApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    float countdownTimer(float time);
    void exit();

    ofSoundPlayer fx;
    Screen * currentScreen;
    GameScreen  gameScreen;
    MenuScreen  menuScreen;
    IntroScreen introScreen;
    EndScreen   endScreen;

    bool LOAD_WITH_SOUND;

private:
    void deleteSaves();
    void resetAllScreens();
    void setupAllScreens();

};
