#ifndef MESSAGE_H
#define MESSAGE_H

#include "GUI.h"
#include <algorithm>

class Message : public GUI {
public:
    Message();
    Message(ofVec2f _pos, string _message);
    Message(ofVec2f _pos, string _message, ofColor _background, ofColor _foreground);
    virtual ~Message();
    void update();
    void draw(float scale, int alpha);
    void changeMessage(string _message);
protected:
private:
    string message;
    float message_life;
    float timer;
    ofTrueTypeFont font;
    ofColor background;
    ofColor foreground;

    ofImage topLeft;
    ofImage topRight;
    ofImage top;
    ofImage left;
    ofImage right;
    ofImage bottomLeft;
    ofImage bottomRight;
    ofImage bottom;
    ofImage center;
    ofImage tail;
};

#endif // MESSAGE_H
