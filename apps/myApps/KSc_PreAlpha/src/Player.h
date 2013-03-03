//
//  Player.h
//  Prototype2
//
//  Created by Diego Garcia on 2/26/13.
//
//

#ifndef __Prototype2__Player__
#define __Prototype2__Player__

#include <iostream>
#include "ofMain.h"
#include "Planet.h"

class Player : public ofBaseApp{
    
public:
    Player();
    Player(int _x, int _y);
    
    void update();
    void draw();
    //void keyPressed(int key);

    void jump();
    void chargeJump();
    void adjustDirPlanet(ofPoint _core, int _size, bool _habitability);
    void move();
    
    ofPoint location;
    ofVec2f dir;
    ofVec2f momentum;
    ofVec2f jumpMom;
    float vel;
    
    bool nearPlanet;
    bool touchingPlanet;
    
    ofVec2f jumpDir;
    float jumpStrength;
    float maxJump;
    
    float ang;
    
    ofVec2f force;
    
    ofVec2f leftDir;
    ofVec2f rightDir;
    
};

#endif /* defined(__Prototype2__Player__) */
