//
//  Planet.cpp
//  Prototype2
//
//  Created by Diego Garcia on 2/24/13.
//
//

#include "Planet.h"

Planet::Planet(){
    
    habitable = true;
    
    
    
}

Planet::Planet(int _x, int _y, int _size, int _gravrange, bool _habitable){
    location.set(_x,_y);
    size = _size;
    gravRange = _gravrange;
    
    habitable = _habitable;
    

    
}

void Planet::update(){
    if(habitable){
        planetColor.set(0,230,100);
    } else {
        planetColor.set(255,0,0);
    }
    
}

void Planet::draw(){
    ofSetColor(230,230,255);
    ofNoFill();
    ofCircle(location,gravRange);
    ofSetColor(planetColor);
    ofFill();
    ofCircle(location,size);
}
