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
    void setActive(bool _ACTIVE) {ACTIVE = _ACTIVE;}
    bool getActive() {return ACTIVE;}

    ofVec2f pos;


    ofColor white;
    ofColor black;
    ofColor red;
    ofColor blue;
    ofColor green;
    ofColor dark_grey;
    ofColor light_blue;
protected:
    bool ACTIVE;
private:

};

#endif // GUI_H
