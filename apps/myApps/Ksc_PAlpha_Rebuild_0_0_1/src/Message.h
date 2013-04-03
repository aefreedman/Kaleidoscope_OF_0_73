#ifndef MESSAGE_H
#define MESSAGE_H

#include "GUI.h"

class Message : public GUI {
public:
    Message();
    Message(ofVec2f _pos, string _message);
    Message(ofVec2f _pos, string _message, ofColor _background, ofColor _foreground);
    virtual ~Message();
    void update();
    void draw();
protected:
private:
    string message;
    float message_life;
    float timer;
    ofColor background;
    ofColor foreground;
};

#endif // MESSAGE_H
