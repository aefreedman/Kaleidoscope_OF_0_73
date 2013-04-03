#ifndef GUI_H
#define GUI_H

#include "Shell.h"

class GUI : public Shell {
public:
    GUI();
    GUI(ofVec2f _pos);
    virtual ~GUI();
    virtual void update();
    virtual void draw();
    void setupColors();

    ofVec2f pos;
    bool ACTIVE;

    ofColor white;
    ofColor black;
    ofColor red;
    ofColor blue;
    ofColor green;
    ofColor dark_grey;
    ofColor light_blue;
protected:

private:
};

#endif // GUI_H
