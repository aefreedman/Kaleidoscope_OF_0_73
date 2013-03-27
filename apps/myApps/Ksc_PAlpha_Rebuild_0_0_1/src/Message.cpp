#include "Message.h"
#define dt 1.0/60.0;

Message::Message() : GUI() {
    //ctor
}

Message::Message(ofVec2f _pos, string _message) : GUI(_pos) {
    pos                     = _pos;
    message                 = _message;
    message_life            = 5;
    DISPLAY                 = true;

}

Message::~Message() {
    //dtor
}

void Message::update() {
    if (DISPLAY) {
        timer += dt;
        if (timer >= message_life) {
            DISPLAY = false;
        }
    }
}


void Message::draw() {
    if (DISPLAY) {
        ofColor dark_grey(25, 25, 25);
        ofColor light_blue(0, 70, 205);
        ofPushMatrix();
        ofDrawBitmapStringHighlight(message, pos, dark_grey, light_blue);
        ofPopMatrix();
    }
}
