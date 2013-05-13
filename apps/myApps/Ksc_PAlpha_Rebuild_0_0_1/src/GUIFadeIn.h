#ifndef GUIFADEIN_H
#define GUIFADEIN_H

#include "GUI.h"


class GUIFadeIn : public GUI {
public:
    GUIFadeIn();
    GUIFadeIn(ofVec2f _pos);
    virtual ~GUIFadeIn();

    void setup();
    void update();
    void draw();
    void setTimer(float fade_time);

protected:
private:
    float timer;
    float init_timer;
    int alpha;

};

#endif // GUIFADEIN_H
