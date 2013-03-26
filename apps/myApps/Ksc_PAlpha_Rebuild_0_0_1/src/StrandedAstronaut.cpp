#include "StrandedAstronaut.h"
#define dt 1.0/60.0

StrandedAstronaut::StrandedAstronaut() : Astronaut() {
    //ctor
}

StrandedAstronaut::StrandedAstronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator) : Astronaut(_pos), gravitator(gravitator) {
    pos                         = _pos;
    r                           = 5;

    //a.set(0, 0);
    //f.set(0, 0);
    dir.set(0, 0);


    FOLLOWING_PLAYER            = false;
}

StrandedAstronaut::~StrandedAstronaut() {
    //dtor
}

/// TODO (Aaron#1#): Astronauts should sit and wait for the player, then follow the player when the player gets close enough to it
void StrandedAstronaut::update() {
    detectPlayerCollisions();
    move();
}

void StrandedAstronaut::draw() {
    ofPushMatrix();
    ofSetColor(100, 100, 100, 255);
    ofFill();
    ofCircle(pos, r);
    ofPopMatrix();
}

void StrandedAstronaut::move() {
    if (FOLLOWING_PLAYER) {
        followPlayer();
    }

    //a  = (f / m) * dt;
    //v += dir * a * dt;
    v += dir * dt;
    //v += gravity * dt;
    //v *= damp;
    pos += v * dt;
}

void StrandedAstronaut::followPlayer() {
    ofVec2f temp;
    temp.set(10, 10);
    //pos = player_pos;
    pos.interpolate(player_pos, .01);

}

void StrandedAstronaut::getPlayerData(ofVec2f _player_pos) {
    player_pos = _player_pos;
}

void StrandedAstronaut::detectPlayerCollisions() {

}
