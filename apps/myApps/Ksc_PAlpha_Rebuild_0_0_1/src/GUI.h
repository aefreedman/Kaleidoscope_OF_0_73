#ifndef GUI_H
#define GUI_H

#include "Shell.h"

class GUI : public Shell {
public:
    GUI();
    GUI(ofVec2f _pos);
    virtual ~GUI();
    virtual void update() = 0;
    virtual void draw() = 0;
    void setupColors();

    ofVec2f pos;
    bool ACTIVE;

protected:
    ofColor white;
    ofColor black;
    ofColor red;
    ofColor blue;
    ofColor green;
    ofColor dark_grey;
    ofColor light_blue;
private:
};

#endif // GUI_H
