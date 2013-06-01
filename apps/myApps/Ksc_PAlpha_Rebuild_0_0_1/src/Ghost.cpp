#include "Ghost.h"




Ghost::Ghost() {
    //ctor
}


Ghost::Ghost(ofVec2f _pos) {
    pos = _pos;
    setup();
}

void Ghost::setup() {
    dir.set(0,-1);
    v = dir * ofRandom(1,2);

    anim = ghost;

    opacity = 0;
    opacityMod = 3;
    IS_DEAD = false;
	dialogueBubble = new Message(pos, "");
    dialogueBubble->changeMessage("Thank you!");
}

void Ghost::update() {

    opacity += opacityMod;
    if (opacity >= 255) {
        opacityMod *= -1;
    } else if (opacity < 0) {
        opacity = 0;
        IS_DEAD = true;
    }

    move();
    dialogueBubble->update();

}

void Ghost::move() {
    pos += v;
    dialogueBubble->pos.set((pos + ofVec2f(10, -35)));
}

void Ghost::draw(float scale) {
    dialogueBubble->draw(scale, opacity);

}






Ghost::~Ghost() {
    //dtor
}
