#include "Player.h"
#define fps 60
#define dt 1/60

Player::Player() : Astronaut() {
    //ctor
}

Player::Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator) : Astronaut(_pos), gravitator(gravitator) {
    setup();
    pos.set(500,500);
    starting_pos.set(pos);

    ofRegisterKeyEvents(this);
    ofAddListener(ofEvents().keyPressed, this, &Player::keyPressed);
    ofAddListener(ofEvents().keyPressed, this, &Player::keyReleased);

    DEBUG = true;
}

Player::~Player() {
}

void Player::setup() {
    w                       = 10;   /// I'm using w as the radius when drawing the player as a circle
    h                       = 10;
    oxygen                  = 100;  /// TODO (Aaron#4#): Couple oxygen to movement ability
    damp                    = 1.00;
    rotation                = 180;
    maxJump                 = 100000;
    m                       = 0.1;
    jumpStrength            = 0;
    G                       = 98;
    /// NOTE (Aaron#2#): Gravity strength is flat for all gravitators
    /// if G is in player & mass is ignored; give planets individual
    /// G or use newtownian forces

    f.set(0,0);
    v.set(0,0);
    dir.set(0, 1);

    ON_PLANET               = false;
    LAND_ON_PLANET          = true;
    USING_GRAVITY           = false;
    ORIENT_TO_PLANET        = true;
    CAN_JETPACK             = true;
    ABSOLUTE_IMPULSE        = true;
    ROTATIONAL_IMPULSE      = false;
    OFF_SCREEN_RESET        = true;
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
        int precision = 0;
        string info = "";
        info += "f: " + ofToString(f, precision) + nl;
        info += "g: " + ofToString(gravity, precision) + nl;
        info += "a: " + ofToString(a, precision) + nl;
        info += "v: " + ofToString(v, precision) + nl;
        info += "pos: " + ofToString(pos, precision) + nl;
        info += "dir: " + ofToString(dir, precision + 2) + nl;
        info += "rot: " + ofToString(rotation) + nl;
        info += "damp: " + ofToString(damp, 2) + nl;
        info += "jump: " + ofToString(jumpDir, 2) + nl;
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
    a   = (f / m) * dt;
    v += dir * a * dt;
    v += gravity * dt;
    v *= damp;
    pos += v * dt;
    f.set(0, 0);
    gravity.set(0, 0);

    if (OFF_SCREEN_RESET){
        if (pos.x > screen_width) {
            pos.set(starting_pos);
            setup();
        }
        if (pos.x < 0) {
            pos.set(starting_pos);
            setup();

        }
        if (pos.y > screen_height) {
            pos.set(starting_pos);
            setup();
        }
        if (pos.y < 0) {
            pos.set(starting_pos);
            setup();
        }
    }

}

void Player::detectPlanetCollisions() {
    ON_PLANET = false;
    IN_GRAVITY_WELL = false;
    EXITED_GRAVITY_WELL = false;

    for (int i = 0; i < gravitator->size(); i++) {
        if (pos.distance((*gravitator)[i]->pos) <= (*gravitator)[i]->r + w) {
            collision = i;
            ON_PLANET = true;
        }
        if (pos.distance((*gravitator)[i]->pos) >= (*gravitator)[i]->r + (w)) {
            LAND_ON_PLANET = true;
        }
        if (pos.distance((*gravitator)[i]->pos) <= (*gravitator)[i]->gR + w) {
            attractor = i;
            IN_GRAVITY_WELL = true;
        }
    }
    if (ON_PLANET && LAND_ON_PLANET) {
            v.set(0, 0);
            LAND_ON_PLANET = false;
        }
    if (ON_PLANET && ORIENT_TO_PLANET) {
            orientToPlanet(collision);
        }
    if (IN_GRAVITY_WELL && LAND_ON_PLANET && USING_GRAVITY) {
            calculateGravity(attractor);
        }
    if (!IN_GRAVITY_WELL) {

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

    /// NOTE (Aaron#5#): Gravity with mass works, but it seems to make everything way too hard.

    gravity                = G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();
    //gravity             = G * (m * planet_mass) / (sqrDist) * planet_to_player_normal.normalized();
    //f                   += gravity;
}

void Player::orientToPlanet(int collision) {
    /// TODO (Aaron#1#): I broke this somehow.
    ofVec2f planet_pos = (*gravitator)[collision]->pos;

    ofVec2f planet_to_player_normal;
    planet_to_player_normal.set(pos - planet_pos);

    ofVec2f perp    = planet_to_player_normal.getPerpendicular();
    ofVec2f up      (0, -1);
    left            = perp;
    right           = -perp;

    jumpDir.set(planet_to_player_normal.getNormalized());

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
    //dir = jumpDir;
    //f += jumpDir * jumpStrength;
    if (!LAND_ON_PLANET) {
    f += jumpStrength;
    }
    //f += normTemp;
    cout << jumpDir * jumpStrength + nl;
    jumpStrength = 0;
}

void Player::keyPressed(ofKeyEventArgs& args) {
    /// TODO (Aaron#9#): Determine why player key listener doesn't apply input (it registers key presses)
    switch (args.key) {
    case 'g':
        //USING_GRAVITY = !USING_GRAVITY;
        break;
    }

    if (ON_PLANET == false) {
        switch (args.key) {
        case OF_KEY_UP:

            break;
        case OF_KEY_LEFT:
            rotation += 10;
            break;
        case OF_KEY_RIGHT:
            rotation -= 10;
            break;
        case OF_KEY_DOWN:
            //int p = 5000;
            //ofVec2f v1(p, p);
            //f += v1;
            cout << "impulsed at " + nl;
            //f.y += 100;
            break;
        case 32:
            chargeJump();
            break;
        }
    }
}

void Player::keyReleased(ofKeyEventArgs& args) {

}
