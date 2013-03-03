//
//  Planet.h
//  Prototype2
//
//  Created by Diego Garcia on 2/24/13.
//
//

#ifndef __Prototype2__Planet__
#define __Prototype2__Planet__

#include <iostream>
#include "ofMain.h"

class Planet: public ofBaseApp{
public:
  
    Planet();
    Planet(int _x, int _y, int _size, int _gravrange, bool _habitable = true);
    void update();
    void draw();
    

    
    ofPoint location;
    int size;
    int gravRange;
    
    bool habitable;
    
    ofColor planetColor;
    
    //float mass;
    
};

#endif /* defined(__Prototype2__Planet__) */
