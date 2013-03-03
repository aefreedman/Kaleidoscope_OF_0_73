//
//  Ship.h
//  Prototype2
//
//  Created by Diego Garcia on 2/24/13.
//
//

#ifndef __Prototype2__Ship__
#define __Prototype2__Ship__

#include <iostream>
#include "ofMain.h"

class Ship : public ofBaseApp{
public:
    Ship();
    Ship(int _x, int _y);
    void update();
    void draw();
    
    int capacity;
    
    bool visible;
    bool blownUp;
    
    ofPoint location;
    
};

#endif /* defined(__Prototype2__Ship__) */
