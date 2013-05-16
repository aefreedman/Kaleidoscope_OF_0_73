#ifndef SCREEN_H
#define SCREEN_H

#include "ofBaseApp.h"
#include "ofMain.h"
#include "GUIFadeIn.h"
#include "GUIFadeOut.h"

class Screen : public ofBaseApp {
public:
    Screen();
    virtual ~Screen();
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    float countdownTimer(float time);

    bool LOAD_WITH_SOUND;
protected:
    virtual void loadResources() = 0;
private:
    GUIFadeIn fadeIn;
    GUIFadeOut fadeOut;
};

#endif // SCREEN_H
