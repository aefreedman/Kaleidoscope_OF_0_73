//
//  Player.cpp
//  Prototype2
//
//  Created by Diego Garcia on 2/26/13.
//
//

#include "Player.h"

//-- setup player ------------------------------------------

Player::Player(){
    
}
//-- setup player at _x,_y ------------------------------------------

Player::Player(int _x, int _y){
    
    location.set(_x,_y);
    dir.set(0,0);
    vel = 2;
    jumpStrength = 0;
    maxJump = 8;
    
    ang = 0;
    
    nearPlanet = false;
    
}

//-- update player ------------------------------------------

void Player::update(){
    
    if (nearPlanet == false) force.set(0,0);
    
    location += dir*vel - momentum;
    
    //ang += 1;
    
    if (ang >= 360 || ang <= -360){
        ang = 0;
    }
    
}


//-- draw player ------------------------------------------

void Player::draw(){
    
    ofSetColor(255,0,0);
    ofNoFill();
    ofCircle(location,20*(jumpStrength/maxJump));
    ofSetColor(0,255,240);
    ofFill();
    ofPushMatrix();
    glTranslatef(location.x,location.y,0);
    glRotatef(ang,0,0,1);
    ofRect(-5,-5,10,10);
    ofRect(-2.5,-10,5,5);
    ofPopMatrix();
    
}

//-- adjust the player's dir based on the planet's grav-------------
void Player::adjustDirPlanet(ofPoint _core, int _size, bool _habitability){
    
    ofVec2f norm;
    norm.set(location.x - _core.x,location.y - _core.y);
    //cout << "THE NORM IS "+ ofToString(norm.length()) + ".    " + "THE SIZE IS " + ofToString(_size) + ".   ";
    if (norm.length() < 5+_size){
        if (_habitability){
        touchingPlanet = true;
        location = _core + norm.scale(5+_size);
        momentum.set(0,0);
        }
        else{
            location.set(0,0);
            dir.set(0,0);
            momentum.set(0,0);
            ang = 0;
        }
    } else {
        touchingPlanet = false;
    ofVec2f newNormal = norm.normalize();
    
    force = .1*(newNormal / (norm.length()*norm.length()));
    momentum += force;
    }
    
    ofVec2f up;
    up.set(0,1);
    
    ang = -norm.angle(up);

    ofVec2f perp;
    perp.set(norm.getPerpendicular());
    
    if (touchingPlanet){
    leftDir = -perp;
    rightDir = perp;
    jumpDir = norm.getNormalized();
    }
    

    
    
}

//-- charge the player's jump --------------------------------------
void Player::chargeJump(){
    if (jumpStrength < maxJump){
        jumpStrength+=.1*maxJump;
    }
}

//-- make the player jump ------------------------------------------

void Player::jump(){
    
    momentum.set(jumpDir*jumpStrength*-1);
    jumpStrength = 0;
    
}
