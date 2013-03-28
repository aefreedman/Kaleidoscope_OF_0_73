#include "Message.h"
#define dt 1.0/60.0;

Message::Message() : GUI() {
    //ctor
}

Message::Message(ofVec2f _pos, string _message) : GUI(_pos) {
    pos                     = _pos;
    message                 = _message;
    message_life            = 5;
    ACTIVE                  = true;
}

Message::~Message() {
    //dtor
}

void Message::update() {
    if (ACTIVE) {
        timer += dt;
        if (timer >= message_life) {
            ACTIVE = false;
        }
    }
}


void Message::draw() {
    if (ACTIVE) {
        ofPushMatrix();
        ofDrawBitmapStringHighlight(message, pos, dark_grey, light_blue);
        ofPopMatrix();
    }
}
