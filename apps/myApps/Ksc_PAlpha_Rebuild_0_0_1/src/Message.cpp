#include "Message.h"

Message::Message() : GUI() {
    //ctor
}

Message::Message(ofVec2f _pos) : GUI(_pos) {
    pos = _pos;
}

Message::~Message() {
    //dtor
}

void Message::update() {

}


void Message::draw() {

}
