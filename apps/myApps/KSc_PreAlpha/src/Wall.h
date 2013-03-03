//
//  Wall.h
//  Prototype2
//
//  Created by Diego Garcia on 2/26/13.
//
//

#ifndef __Prototype2__Wall__
#define __Prototype2__Wall__

#include <iostream>
#include "ofMain.h"

class Wall : public ofBaseApp{
public:
    Wall();
    Wall(int _x, int _y, int _width, int _height);
    
    void update();
    void draw();
    
    ofPoint location;
    int width;
    int height;
    
    //bool movable;

};

#endif /* defined(__Prototype2__Wall__) */
