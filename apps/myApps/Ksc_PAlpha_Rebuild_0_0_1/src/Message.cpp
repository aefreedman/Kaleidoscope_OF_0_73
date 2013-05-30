#include "Message.h"
#define dt 1.0/60.0;

Message::Message() : GUI() {
    //ctor
}

Message::Message(ofVec2f _pos, string _message) : GUI(_pos) {
    pos                     = _pos;
    message                 = _message;
    message_life            = 5;
    ACTIVE                  = false;
    background              = dark_grey;
    foreground              = light_blue;

    topLeft.loadImage("ART/message/TL.png");
    topRight.loadImage("ART/message/TR.png");
    top.loadImage("ART/message/T.png");
    right.loadImage("ART/message/R.png");
    left.loadImage("ART/message/L.png");
    bottomLeft.loadImage("ART/message/BL.png");
    bottomRight.loadImage("ART/message/BR.png");
    bottom.loadImage("ART/message/B.png");
    center.loadImage("ART/message/C.png");
    tail.loadImage ("ART/message/tail.png");

    font.loadFont("fonts/pixelmix.ttf",8);
}

Message::Message(ofVec2f _pos, string _message, ofColor _background, ofColor _foreground) : GUI(_pos) {
    pos                     = _pos;
    message                 = _message;
    message_life            = 5;
    ACTIVE                  = false;
    background              = _background;
    foreground              = _foreground;
}

Message::~Message() {
    //dtor
}

void Message::update() {
    if (ACTIVE) {
        timer += dt;
        if (timer >= message_life) {
            ACTIVE = false;
            timer = 0;
        }
    }
}

void Message::changeMessage(string _message) {
    message = _message;
    ACTIVE = true;
}

void Message::draw() {

    ofSetMinMagFilters(GL_NEAREST, GL_NEAREST);
    if (ACTIVE) {

        int lines = std::count(message.begin(), message.end(), '\n')+ 4;
        int bubWidth = (message.length() / (lines -3)) + 3;





        ofPushMatrix();
        ofSetColor(255,255,255,255);
        for (int y = 0; y<lines; y++){
            for (int x = 0; x < bubWidth; x++){

            ofPoint drawPos;
            drawPos.set(pos.x+(x*8)-4,pos.y+(y*8)-16);

                    if (y == 0 && x == 0){
                        topLeft.draw(drawPos);
                    } else if ( y == 0 && x == bubWidth - 1) {
                        topRight.draw(drawPos);
                    }else if ( y == lines-1 && x == 0) {
                        bottomLeft.draw(drawPos);
                    }else if (y == 0) {
                        top.draw(drawPos);
                    } else if (x == 0) {
                        left.draw(drawPos);
                    } else if ( y == lines-1 && x == bubWidth-1) {
                        bottomRight.draw(drawPos);
                    } else if (x == bubWidth-1){
                        right.draw(drawPos);
                    } else if (y == lines-1){
                        bottom.draw(drawPos);
                    } else {
                        center.draw(drawPos);
                    }
            }
        }

        tail.draw(pos.x + 2, pos.y + lines*8 - 16);
        ofSetColor(175,247,236);
        //ofDrawBitmapStringHighlight(message, pos, background, foreground);
        //ofDrawBitmapString(message,pos);
        font.drawString(message,pos.x,pos.y);
        ofPopMatrix();
    }
}
