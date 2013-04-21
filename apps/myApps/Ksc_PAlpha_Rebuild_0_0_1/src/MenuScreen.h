#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"


class MenuScreen : public Screen {
public:
    MenuScreen();
    virtual ~MenuScreen();

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
protected:
private:
};

#endif // MENUSCREEN_H
