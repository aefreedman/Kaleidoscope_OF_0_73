#include "Player.h"

Player::Player() : Astronaut() {
    //ctor
}

Player::Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator) : Astronaut(_pos), gravitator(gravitator) {
    //pos = _pos;
    pos.set(500,500);
    w = 50;
    h = 70;
    dir.set(0,0);
    v.set(0,0);
    damp = 0.95;
    rotation = 0;
    momentum.set(0, 0);
    f.set(0,0);
    maxJump = 8;
}

Player::~Player() {
}

void Player::setup() {
    ofRegisterKeyEvents(this);
}

void Player::update() {
    getNearPlanet();
    move();

    //Debug
    /*
    if (nearPlanet) {
    cout << "NEARPLANET!\n";
    }
    if (!nearPlanet) {
        cout << "NOTNEARPLANET!\n";
    }
    */
    //cout << ofToString(pos) + "\n";

}

void Player::draw() {
    ofSetColor(255,0,0);
    ofNoFill();
    ofCircle(pos,20*(jumpStrength/maxJump));
    ofSetColor(0,255,240);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x,pos.y,0);
    glRotatef(rotation,0,0,1);
    ofRect(-5,-5,10,10);
    ofRect(-2.5,-10,5,5);
    ofPopMatrix();
}

void Player::move() {
    if (nearPlanet == false) {
        f.set(0,0);
    }
    if (rotation >= 360 || rotation <= -360){
        rotation = 0;
    }
    pos += dir * v - momentum;

    //v *= damp;
    //pos += rotation * v - momentum;
}

void Player::getNearPlanet() {
    nearPlanet = false;
    for (int i = 0; i < gravitator->size(); i++) {
        if (pos.distance((*gravitator)[i]->pos) < (*gravitator)[i]->gR) {
            nearPlanet = true;
            orientToPlanet((*gravitator)[i]->pos, (*gravitator)[i]->gR, (*gravitator)[i]->r, (*gravitator)[i]->habitable);
            closestPlanet = i;
        }
    }
}

void Player::orientToPlanet(ofVec2f cOfGrav, float gR, float r, bool habitable) {
    ofVec2f norm;
    norm.set(pos - cOfGrav);
    cout << "THE NORM IS "+ ofToString(norm.length()) + ".    " + "THE SIZE IS " + ofToString(r) + ".   ";
    if (norm.length() < 5 + r) {
        if (habitable) {
            touchingPlanet = true;
            pos = cOfGrav + norm.scale(5 + r);
            momentum.set(0,0);
        } else {
            pos.set(0,0);
            dir.set(0,0);
            momentum.set(0,0);
            rotation = 0;
        }
    } else {
        touchingPlanet = false;
        ofVec2f newNormal = norm.normalize();

        f = .1*(newNormal / (norm.length() * norm.length()));
        momentum += f;
    }

    ofVec2f up;
    up.set(0,1);

    rotation = -norm.angle(up);

    ofVec2f perp;
    perp.set(norm.getPerpendicular());

    if (touchingPlanet) {
        leftDir = -perp;
        rightDir = perp;
        jumpDir = norm.getNormalized();
    }
}

void Player::gravity() {

}

void Player::keyPressed(ofKeyEventArgs& args) {
    //Broken: not detecting key presses
    if (args.key == '1') {
        v.x = -100.0;
        cout << "sdfds";
    }
    if (args.key == 'd') {
        v.x = 100.0;
    }
    if (args.key == 'w') {
        v.y = -100.0;
    }
    if (args.key == 's') {
        v.y = 100.0;
    }
}

void Player::keyReleased(ofKeyEventArgs& args) {

}

void Player::chargeJump() {
    if (jumpStrength < maxJump){
        jumpStrength += 0.10 * maxJump;
    }
}

void Player::jump() {
    momentum.set(jumpDir * jumpStrength * -1);
    jumpStrength = 0;

}
