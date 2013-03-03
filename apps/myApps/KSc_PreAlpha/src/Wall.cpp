//
//  Wall.cpp
//  Prototype2
//
//  Created by Diego Garcia on 2/26/13.
//
//

#include "Wall.h"

Wall::Wall(){
    
}


Wall::Wall(int _x, int _y, int _width, int _height){
    location.set(_x,_y);
    width = _width;
    height = _height;
    
}


void Wall::update(){
    
}


void Wall::draw(){
    ofSetColor(0,0,255);
    ofRect(location,width,height);
    
}