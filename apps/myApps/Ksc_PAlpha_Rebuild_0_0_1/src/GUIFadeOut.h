#ifndef GUIFADEOUT_H
#define GUIFADEOUT_H

#include "GUI.h"

class GUIFadeOut : public GUI {
public:
    GUIFadeOut();
    GUIFadeOut(ofVec2f _pos);
    virtual ~GUIFadeOut();
    int getAlpha();

    void setup();
    void update();
    void draw();
    float timer;
    float max_timer;

    enum {BLACK = 255};
protected:
private:

    int alpha;
};

#endif // GUIFADEOUT_H
