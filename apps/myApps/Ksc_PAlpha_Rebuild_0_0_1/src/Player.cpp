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
    w                       = 10;
    h                       = 10;
    r                       = 5;
    oxygen                  = 100;  /// TODO (Aaron#4#): Couple oxygen to movement ability
    damp                    = 1.00;
    rotation                = 180;
    maxJump                 = 100000;
    m                       = 0.1;
    jumpStrength            = 0;
    G                       = 98;
    restitution             = 0.75; /// Used to calculate the amount of momentum conserved when bouncing off a planet
    off_screen_limit        = 200;

    /// NOTE (Aaron#2#): Gravity strength is flat for all gravitators
    /// if G is in player & mass is ignored; give planets individual
    /// G or use newtownian forces

    f.set(0,0);
    v.set(0,0);
    dir.set(0, 1);

    ON_PLANET               = false;
    CAN_LAND_ON_PLANET      = true;
    USING_GRAVITY           = true;
    ORIENT_TO_PLANET        = true;
    CAN_JETPACK             = true;
    ABSOLUTE_IMPULSE        = false;
    ROTATIONAL_IMPULSE      = true;
    OFF_SCREEN_RESET        = true;
    SIMPLE_GRAVITY          = false;

    /// TODO (Aaron#2#): Create failsafe to prevent ABSOLUTE & ROTATIONAL from both being true
}

void Player::update() {
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
    ofCircle(0, 0, r);
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
        info += "f: " + ofToString(display_f, precision) + nl;
        if (SIMPLE_GRAVITY) {
        info += "g: " + ofToString(display_g, precision) + " (simple)" + nl;
        } else {
        info += "g: " + ofToString(display_g, precision) + " (realistic)" + nl;
        }
        info += "a: " + ofToString(display_a, precision) + nl;
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

    a  = (f / m) * dt;
    v += dir * a * dt;
    v += gravity * dt;
    v *= damp;
    pos += v * dt;
    display_f = m / a;

    f.set(0, 0);
    gravity.set(0, 0);

    if (OFF_SCREEN_RESET){
        if (pos.x > screen_width + off_screen_limit) {
            pos.set(starting_pos);
            setup();
        }
        if (pos.x < -off_screen_limit) {
            pos.set(starting_pos);
            setup();

        }
        if (pos.y > screen_height + off_screen_limit) {
            pos.set(starting_pos);
            setup();
        }
        if (pos.y < -off_screen_limit) {
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
        float dist                  = pos.distance((*gravitator)[i]->pos);
        int planet_r              = (*gravitator)[i]->r;
        int planet_gravity_range  = (*gravitator)[i]->gR;

        if (dist <= planet_r + r) {
            collision = i;
            ON_PLANET = true;
        }
        if (dist >= planet_r + (r * 2)) {
            CAN_LAND_ON_PLANET = true;
        }
        if (dist <= planet_gravity_range + r) {
            attractor = i;
            IN_GRAVITY_WELL = true;
        }
    }

    if (ON_PLANET && CAN_LAND_ON_PLANET) {
            CAN_LAND_ON_PLANET = false;
        }
    if (ON_PLANET && ORIENT_TO_PLANET) {
            orientToPlanet(collision);
        }
    if (IN_GRAVITY_WELL && CAN_LAND_ON_PLANET && USING_GRAVITY) {
            calculateGravity(attractor);
        }
    if (!IN_GRAVITY_WELL) {

        }
}

bool Player::detectCollisions() {
    for (int i = 0; i < gravitator->size(); i++) {
        float dist = pos.distance((*gravitator)[i]->pos);
        float sum_radii = r + (*gravitator)[i]->r;
        dist -= sum_radii;
    }
}

void Player::bounce() {

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
    if (SIMPLE_GRAVITY) {
    gravity               += G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();
    } else {
    gravity               += G * (m * planet_mass) / (sqrDist) * planet_to_player_normal.normalized();
    }
    display_g.set(gravity);
}

void Player::orientToPlanet(int collision) {
    ofVec2f planet_pos = (*gravitator)[collision]->pos;
    int planet_m = (*gravitator)[collision]->m;

    ofVec2f planet_to_player_normal;
    planet_to_player_normal.set(pos - planet_pos);
    ofVec2f normalized_normal = planet_to_player_normal.getNormalized();

    ofVec2f perp    = planet_to_player_normal.getPerpendicular();
    ofVec2f up      (0, -1);
    left            = perp;
    right           = -perp;

    jumpDir.set(normalized_normal);

    float a1 = v.dot(normalized_normal);
    float optimizedP = (2.0 * a1) / (m + planet_m);
    ofVec2f v_prime = v - optimizedP * planet_m * normalized_normal;
    v_prime *= restitution;

    v.set(v_prime);

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
    if (!CAN_LAND_ON_PLANET) {
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
