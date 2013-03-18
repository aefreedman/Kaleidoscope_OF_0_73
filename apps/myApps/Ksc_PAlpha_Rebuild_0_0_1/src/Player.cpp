#include "Player.h"
#define fps 60
#define dt 1/60

Player::Player() : Astronaut() {
    //ctor
}

Player::Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator) : Astronaut(_pos), gravitator(gravitator) {
    //pos = _pos;
    w               = 10;
    h               = 10;
    damp            = 0.99;
    rotation        = 0;
    maxJump         = 1;
    m               = 1;
    jumpStrength    = 0;
    G               = 98;

    f.set(0,0);
    v.set(0,0);
    pos.set(500,500);
    dir.set(0, 0);

    //dt = 1 / fps;

    //ofRegisterKeyEvents(this);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyPressed);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyReleased);

    DEBUG = true;
}

Player::~Player() {
}

void Player::setup() {

}

void Player::update() {
    detectPlanetCollisions();
    move();

}

void Player::draw() {
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofCircle(pos,20 * (jumpStrength / maxJump));
    ofSetColor(0, 255, 240);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(rotation,0, 0, 1);
    ofRect(-5, -5, w, h);
    ofRect(-2.5, -10, w/2, h/2);
    ofPopMatrix();

    //Player info debug

    if (DEBUG) {

    string info = "";
    string nl  = "\n";
    info += "f: " + ofToString(f) + nl;
    info += "g: " + ofToString(gravity) + nl;
    info += "a: " + ofToString(a) + nl;
    info += "v: " + ofToString(v) + nl;
    info += "pos: " + ofToString(pos) + nl;

    if (ON_PLANET) {
    info += "ON_PLANET" + nl;
    }
    if (IN_GRAVITY_WELL) {
    info += "IN_GRAVITY_WELL" + nl;
    }
    ofSetColor(240, 0, 20);
    ofDrawBitmapString(info, 30, 600);
    }
}

void Player::move() { ///Euler integration & rotation correction
    //if (rotation >= 360 || rotation <= -360){
    //    rotation = 0;
    //}
    //a   = f / m;
    //v   += a * dt;
    //v   += gravity * dt;
    //v   *= damp;
    //v *= 0.25;
    //pos += v * dir;
    //pos += v * dt;

    v += gravity * dt;
    pos += v * dt;
}

void Player::detectPlanetCollisions() {
    ON_PLANET = false;
    IN_GRAVITY_WELL = false;
    EXITED_GRAVITY_WELL = false;

    for (int i = 0; i < gravitator->size(); i++) {
        if (pos.distance((*gravitator)[i]->pos) <= (*gravitator)[i]->r) {
            collision = i;
            ON_PLANET = true;
        }
        if (pos.distance((*gravitator)[i]->pos) <= (*gravitator)[i]->gR) {
            attractor = i;
            IN_GRAVITY_WELL = true;
        }
        if (pos.distance((*gravitator)[i]->pos) <= (*gravitator)[i]->gR) {
            attractor = i;
            IN_GRAVITY_WELL = true;
        }
        if (ON_PLANET == true) {
            orientToPlanet(collision);
            //gravity.set(0, 0);
            //f.set(0, 0);
            //v.set(0, 0);
        }
        if (IN_GRAVITY_WELL && !ON_PLANET) {
            damp = 1.0;
            calculateGravity(attractor);
        }
        if (!IN_GRAVITY_WELL) {
            gravity.set(0, 0);
            f.set(0, 0);
            damp = 1.0;

        }
    }
}

void Player::calculateGravity(int attractor) {
    ofVec2f planet_pos = (*gravitator)[attractor]->pos;
    int planet_gravity_range = (*gravitator)[attractor]->gR;
    int planet_size =  (*gravitator)[attractor]->r;
    int planet_mass = (*gravitator)[attractor]->m;

    ofVec2f planet_to_player_normal;
    //planet_to_player_normal.set(pos - planet_pos);
    planet_to_player_normal.set(planet_pos - pos);
    ofVec2f sqrDist;
    sqrDist.set(pos.squareDistance(planet_pos));

    gravity                = G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();

    //gravity             = G * (m * planet_mass) / (sqrDist) * planet_to_player_normal.normalized();
    f                   += gravity;
}

void Player::orientToPlanet(int collision) {
    ofVec2f PLANET_POS = (*gravitator)[collision]->pos;

    ofVec2f PLANET_TO_PLAYER_NORMAL;
    PLANET_TO_PLAYER_NORMAL.set(pos - PLANET_POS);
    ofVec2f perp    = PLANET_TO_PLAYER_NORMAL.getPerpendicular();
    //ofVec2f down    (0, -1);
    ofVec2f up      (0, -1);
    left            = -perp;
    right           = perp;
    jumpDir         = -PLANET_TO_PLAYER_NORMAL.getNormalized();
    rotation        = PLANET_TO_PLAYER_NORMAL.angle(up);
}

inline Player::AngularVelocityToSpin( ofQuaternion orientation, ofVec2f angular_v )
{
    float x = angular_v.x();
    float y = angular_v.y();
    float z = 0.0;
    return 0.5 * ofQuaternion( 0, x, y, z ) * orientation;
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

    if (ON_PLANET == false) {
        switch (args.key) {
        case OF_KEY_UP:
            pos.set(100, 100);
            break;
        case OF_KEY_LEFT:
            rotation += 10;
            break;
        case OF_KEY_RIGHT:
            rotation -= 10;
            break;
        case OF_KEY_DOWN:
            f.y += 100;
            break;
        case 32:
            chargeJump();
            break;
        }
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

}

void Player::keyReleased(ofKeyEventArgs& args) {

}
