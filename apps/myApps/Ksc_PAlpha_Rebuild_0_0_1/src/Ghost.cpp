#include "Ghost.h"




Ghost::Ghost()
{
    //ctor
}


Ghost::Ghost(ofVec2f _pos){
    pos = _pos;
    setup();
}

void Ghost::setup(){
    dir.set(0,-1);
    v = dir * ofRandom(1,2);

    anim = ghost;

    opacity = 0;
    opacityMod = 5;
    IS_DEAD = false;
}

void Ghost::update(){

    opacity += opacityMod;
    if (opacity >= 255){
        opacityMod *= -1;
    } else if (opacity < 0){
        opacity = 0;
        IS_DEAD = true;
    }

    move();

}

void Ghost::move(){

        pos += v;

}

void Ghost::draw(){

}






Ghost::~Ghost()
{
    //dtor
}
