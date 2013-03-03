//
//  Ship.cpp
//  Prototype2
//
//  Created by Diego Garcia on 2/24/13.
//
//

#include "Ship.h"

Ship::Ship(){
    
    capacity = 1;
    visible = true;
    blownUp = false;
    
}

Ship::Ship(int _x, int _y){
    
    location.set(_x,_y);
    capacity = 1;
    visible = true;
    blownUp = false;
}

void Ship::update(){
    
    if(blownUp){
        visible = false;
    } else {
        visible = true;
    }
    
}

void Ship::draw(){
    if(visible){
        ofSetColor(255,100,100);
        ofRect(location,20,10);
    }
}