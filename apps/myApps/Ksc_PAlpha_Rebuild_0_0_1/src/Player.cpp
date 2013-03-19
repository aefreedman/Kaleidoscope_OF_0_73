#include "Player.h"
#define fps 60
#define dt 1/60

Player::Player() : Astronaut() {
    //ctor
}

Player::Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator) : Astronaut(_pos), gravitator(gravitator) {
    setup();
    pos.set(500,500);

    //ofRegisterKeyEvents(this);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyPressed);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyReleased);

    DEBUG = true;
}

Player::~Player() {
}

void Player::setup() {
    w                       = 10;
    h                       = 10;
    oxygen                  = 100;  /// TODO (Aaron#4#): Couple oxygen to movement ability
    damp                    = 0.95;
    rotation                = 0;
    maxJump                 = 100;
    m                       = 1;
    jumpStrength            = 0;
    G                       = 98;
    /// NOTE (Aaron#2#): Gravity strength is flat for all gravitators
    /// if G is in player & mass is ignored; give planets individual
    /// G or use newtownian forces

    f.set(0,0);
    v.set(0,0);
    dir.set(0, -1);

    ORIENT_TO_PLANET        = false;
    CAN_JETPACK             = true;
    ABSOLUTE_IMPULSE        = true;
    ROTATIONAL_IMPULSE      = false;
    /// TODO (Aaron#2#): Create failsafe to prevent ABSOLUTE & ROTATIONAL from both being true
}

void Player::update() {
    /// TODO (Aaron#1#): Implement simple circle-circle collisions
    detectPlanetCollisions();
    move();

}

void Player::draw() {
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofCircle(pos, 20 * (jumpStrength / maxJump));
    ofSetColor(0, 255, 240);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(rotation,0, 0, 1);
    ofCircle(0, 0, 5);
    //ofRect(-5, -5, w, h);
    //ofRect(-2.5, 5, w/2, h/2);
    ofLine(ofPoint(0, 0), ofPoint(0, -100));
    ofPopMatrix();

    if (DEBUG) {
        int x = 30;
        int y = 550;
        int column_width = 100;
        int PRECISION = 0;
        string info = "";
        info += "f: " + ofToString(f, PRECISION) + nl;
        info += "g: " + ofToString(gravity, PRECISION) + nl;
        info += "a: " + ofToString(a, PRECISION) + nl;
        info += "v: " + ofToString(v, PRECISION) + nl;
        info += "pos: " + ofToString(pos, PRECISION) + nl;
        info += "dir: " + ofToString(dir, PRECISION + 2) + nl;
        info += "rot: " + ofToString(rotation) + nl;
        info += "damp: " + ofToString(damp, 2) + nl;
        ofSetColor(240, 0, 20);
        ofDrawBitmapString(info, x, y);

        /// FIXME (Aaron#3#): Why is this only displaying the ends of long strings?
        string info_b = "";
        if (ON_PLANET) {
            info_b += "Testlkjlkjlkjlkjlkjlkj" + nl;
        }
        if (IN_GRAVITY_WELL) {
            info_b += "Test2lkjlkjlkjlkjlkjlkjl" + nl;
        }
        ofSetColor(240, 0, 20);
        ofDrawBitmapString(info_b, x + column_width, y);
    }
}

void Player::move() {
    if (rotation >= 360 || rotation <= -360){
        rotation = 0;
    }

    /// FIXME (Aaron#1#): Determine source of direction & forces error (where should dir apply?)
    //f   = f * dir;
    a   = (f / m);
    //v   += a * dt;
    //v   += gravity * dt;
    //v *= 0.25;
    //pos += v * dir;
    //pos += v * dt;

    v += dir * a * dt;
    v += gravity * dt;
    v *= damp;
    //pos += dir * v * dt;
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
        if (ON_PLANET) {
            v *= -1;
        }
        if (ON_PLANET && ORIENT_TO_PLANET) {
            orientToPlanet(collision);
        }
        if (IN_GRAVITY_WELL && !ON_PLANET) {
            calculateGravity(attractor);
        }
        if (!IN_GRAVITY_WELL) {
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
    //gravity                = G * planet_to_player_normal.normalized() / sqrDist;

    //gravity             = G * (m * planet_mass) / (sqrDist) * planet_to_player_normal.normalized();
    //f                   += gravity;
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

inline ofQuaternion Player::AngularVelocityToSpin(ofQuaternion orientation, ofVec2f angular_v) {
    float x = angular_v.x;
    float y = angular_v.y;
    float z = 0.0;
    ofQuaternion q;
    //spin.x 0.5 * ofQuaternion( 0, x, y, z ) * orientation;
    q.set(0, x, y, z);
    //return 0.5 * q * orientation;
}


void Player::chargeJump() {
    if (jumpStrength < maxJump) {
        jumpStrength += 0.10 * maxJump;
    }
}

void Player::jump() {
    //f += dir * jumpStrength;
    v += jumpStrength;
    //f += normTemp;
    jumpStrength = 0;
}

void Player::keyPressed(ofKeyEventArgs& args) {
    /// TODO (Aaron#9#): Determine why player key listener doesn't apply input (it registers key presses)
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
}

void Player::keyReleased(ofKeyEventArgs& args) {

}
