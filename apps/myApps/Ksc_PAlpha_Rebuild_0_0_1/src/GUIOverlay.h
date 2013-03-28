#ifndef GUIOVERLAY_H
#define GUIOVERLAY_H

#include "GUI.h"

class GUIOverlay : public GUI {
public:
    GUIOverlay();
    GUIOverlay(ofVec2f _pos, string _display_text);
    virtual ~GUIOverlay();

    void update();
    void draw();
protected:
private:
    string display_text;
};

#endif // GUIOVERLAY_H
