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

    ofVec2f pos;

protected:
    //ofColor dark_grey;
    //ofColor light_blue;
private:
};

#endif // GUI_H
