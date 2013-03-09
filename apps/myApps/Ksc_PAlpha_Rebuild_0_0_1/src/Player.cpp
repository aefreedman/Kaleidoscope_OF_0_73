#include "Player.h"

Player::Player() : Astronaut() {
    //ctor
}

Player::Player(ofVec2f _pos) : Astronaut(_pos) {
    pos = _pos;
    w = 50;
    h = 70;
    v.set(0.01, -0.01);

}

Player::~Player() {
}

void Player::update() {
    move();
}

void Player::draw() {
    ofPushMatrix();
    ofColor player(0, 180, 60);
    ofSetColor(player);
    ofFill();
    ofRect(pos, w, h);
    ofPopMatrix();
}

void Player::move() {
    pos += v;
}
