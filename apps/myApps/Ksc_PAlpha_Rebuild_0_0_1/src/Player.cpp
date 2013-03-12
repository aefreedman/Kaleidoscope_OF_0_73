#include "Player.h"

Player::Player() : Astronaut() {
    //ctor
}

Player::Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator) : Astronaut(_pos), gravitator(gravitator) {
    //pos = _pos;
    w               = 50;
    h               = 70;
    damp            = 0.99;
    rotation        = 0;
    maxJump         = 200;
    m               = 10;
    jumpStrength    = 0;
    G               = 2;

    f.set(0,0);
    v.set(0,0);
    pos.set(500,500);
}

Player::~Player() {
}

void Player::setup() {
    //ofRegisterKeyEvents(this);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyPressed);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyReleased);
}

void Player::update() {
    getNearPlanet();
    move();
}

void Player::draw() {
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofCircle(pos,20 * (jumpStrength / maxJump));
    ofSetColor(0, 255, 240);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x,pos.y, 0);
    glRotatef(rotation,0, 0, 1);
    ofRect(-5, -5, 10, 10);
    ofRect(-2.5, -10, 5, 5);
    ofPopMatrix();
}

void Player::move() {
    if (nearPlanet == false) {
        //f.set(0,0);
    }
    if (rotation >= 360 || rotation <= -360){
        rotation = 0;
    }

    a   = f / m;
    v   += a;
    v   *= damp;
    pos += v;
}

void Player::getNearPlanet() {
    nearPlanet = false;
    for (int i = 0; i < gravitator->size(); i++) {
        if (pos.distance((*gravitator)[i]->pos) <= (*gravitator)[i]->gR) {
            nearPlanet = true;
            orientToPlanet((*gravitator)[i]->pos, (*gravitator)[i]->gR, (*gravitator)[i]->r, (*gravitator)[i]->habitable, (*gravitator)[i]->m);
        }

    }
}

void Player::orientToPlanet(ofVec2f cOfGrav, float gR, float r, bool habitable, int mBody) {
    ofVec2f normal;
    normal.set(pos - cOfGrav);
    ofVec2f perp    = normal.getPerpendicular();
    ofVec2f down    (0, -1);
    ofVec2f up      (0, 1);
    left            = -perp;
    right           = perp;
    jumpDir         = normal.getNormalized();
    rotation        = -normal.angle(up);
    ofVec2f sqrDist;
    sqrDist.set(pos.squareDistance(cOfGrav));

    ///Collision detection
    touchingPlanet = false;
    for (int i = 0; i < gravitator->size(); i++) {
        if (pos.distance((*gravitator)[i]->pos) <= (*gravitator)[i]->r) {
            touchingPlanet = true;
            cout << "hit planet!";
        }
    }

    int a = 30;

    if (touchingPlanet) {
        pos                 = cOfGrav + normal.scale(r);
        damp                = 0.80;
        //f                   = G * (m * mBody) / (sqrDist) * normal.normalized();
    } else {
        damp                = 0.99;
        f                   = -G * (m * mBody) / (sqrDist) * normal.normalized();
    }

    //cout << "THE NORM IS "+ ofToString(norm.length()) + ".    " + "THE SIZE IS " + ofToString(r) + ".   ";
    /*
    int a = 10;
    if (normal.length() < a + r) { ///hitting planet
        if (habitable) {
            touchingPlanet      = true;
            pos                 = cOfGrav + normal.scale(a + r);
        } else {
            //pos.set(0, 0);
            //rotation = 0;
        }
    } else { ///not hitting planet
            touchingPlanet      = false;
            f                   = -normal.normalize() * (9.80 * (m * mBody) / (gR * gR));
    }
    */
    //f += left;
    //f += .1 * right;
}

void Player::gravity() {

}

void Player::chargeJump() {
    if (jumpStrength < maxJump){
        jumpStrength += 0.10 * maxJump;
    }
}

void Player::jump() {
    f += (jumpDir * jumpStrength);
    //f += normTemp;
    jumpStrength = 0;
}

void Player::keyPressed(ofKeyEventArgs& args) {
    /*
    switch (args.key) {
    case OF_KEY_UP:
        cout << "sadflkjdsflkj";
        break;
    case OF_KEY_LEFT:
        break;
    case OF_KEY_RIGHT:
        break;
    case 32:
        chargeJump();
        break;
    }


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
    */
}

void Player::keyReleased(ofKeyEventArgs& args) {

}
