#include "Player.h"
#define fps 60
#define dt 1.0/60.0

Player::Player() : Astronaut() {
    //ctor
}

Player::Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut) : Astronaut(_pos), gravitator(gravitator), strandedAstronaut(strandedAstronaut) {
    setup();
    pos.set(500,500);
    starting_pos.set(pos);

    ofRegisterKeyEvents(this);
    ofAddListener(ofEvents().keyPressed, this, &Player::keyPressed);
    ofAddListener(ofEvents().keyPressed, this, &Player::keyReleased);

    DEBUG = false;
}

Player::~Player() {
}

void Player::setup() {
    w                       = 10;
    h                       = 10;
    r                       = 5;
    oxygen                  = 100.0;
    damp                    = 1.00;
    rotation                = 180;
    maxJump                 = 1000000.0;
    m                       = 1.0;
    jumpStrength            = 0.0;
    G                       = 100.0;
    restitution             = 0.10; /// Used to calculate the amount of momentum conserved when bouncing off a planet
    off_screen_limit        = 200;
    rotation_speed          = 3.0;
    speed_on_planet         = 150.0;
    jetpack_power           = 50000.0;
    jump_multiplier         = 30.0;
    jetpack_o2_use          = 5;

    /// NOTE (Aaron#2#): Gravity strength is flat for all gravitators
    /// if G is in player & mass is ignored; give planets individual
    /// G or use newtownian forces

    f.set(0,0);
    v.set(0,0);
    dir.set(-1, 0);

    ON_PLANET               = false;
    CAN_LAND_ON_PLANET      = true;
    USING_GRAVITY           = true;
    ORIENT_TO_PLANET        = true;
    CAN_JETPACK             = true;
    ABSOLUTE_IMPULSE        = false;
    ROTATIONAL_IMPULSE      = true;
    OFF_SCREEN_RESET        = true;
    SIMPLE_GRAVITY          = true;
    GUI                     = true;
    TRAVERSING_PLANET       = false;

    /// TODO (Aaron#2#): Create failsafe to prevent ABSOLUTE & ROTATIONAL from both being true
}

void Player::update() {
    detectGravitatorCollisions();
    display_g.set(gravity);
    detectAstronautCollisions();
    move();
}

void Player::draw() {
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofCircle(pos, (20 * (jumpStrength / maxJump)) + r) ;
    ofSetColor(0, 255, 240);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(rotation,0, 0, 1);
    ofCircle(0, 0, r);
    //ofRect(-5, -5, w, h);
    //ofRect(-2.5, 5, w/2, h/2);
    ofLine(ofPoint(0, 0), ofPoint(100, 0));
    ofPopMatrix();

    if (GUI) {
        drawGUI();
    }
}

void Player::drawGUI() {
    int x = 1000;
    int y = 600;
    string gui = "";
    gui += "O2: " + ofToString(oxygen, 6) + nl;
    ofSetColor(0, 50, 255);
    ofDrawBitmapString(gui, x, y);

    if (DEBUG) {
        int x = 30;
        int y = 550;
        int column_width = 400;
        int precision = 0;
        string info = "";
        info += "DEBUG MENU" + nl;
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
        info += "maxJump: " + ofToString(maxJump, 2) + nl;

        ofSetColor(240, 0, 20);
        ofDrawBitmapString(info, x, y);

        /// FIXME (Aaron#3#): Why is this only displaying the ends of long strings?
        string info_b = "";
        if (ON_PLANET) {
            info_b.append("ON THE PLANET, BRO \n");
        }
        if (IN_GRAVITY_WELL) {
            info_b.append("IN THE GRAVITY WELL, BRO \n");
        }
        if (CAN_LAND_ON_PLANET) {
            info_b.append("CAN LAND ON PLANET, BRO \n");
        } else {
            info_b.append("LANDED ON THE PLANET, BRO \n");
        }
        if (TRAVERSING_PLANET) {
            info_b.append("TRAVERSING THE PLANET, BRO \n");
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

void Player::detectAstronautCollisions() {
    for (int i = 0; i < strandedAstronaut->size(); i++) {
        float dist                  = pos.distance((*strandedAstronaut)[i]->pos);
        float astronaut_r           = (*strandedAstronaut)[i]->r;

        if (dist <= r + astronaut_r) {
            (*strandedAstronaut)[i]->FOLLOWING_PLAYER = true;
            cout << "I'm Astronaut #" + ofToString(i) + " and I'm following you!" << endl;
        }
        if ((*strandedAstronaut)[i]->FOLLOWING_PLAYER == true) {
            (*strandedAstronaut)[i]->getPlayerData(pos);
        }
    }
}

void Player::detectGravitatorCollisions() {
    ON_PLANET = false;
    IN_GRAVITY_WELL = false;
    EXITED_GRAVITY_WELL = false;

    for (int i = 0; i < gravitator->size(); i++) {
        float dist                  = pos.distance((*gravitator)[i]->pos);
        string gravitator_type      = (*gravitator)[i]->type;
        int planet_r                = (*gravitator)[i]->r;
        int planet_gravity_range    = (*gravitator)[i]->gR;

        if (dist <= planet_r + r && gravitator_type == "planet") {
            collision               = i;
            ON_PLANET               = true;
        }
        if (dist >= planet_r + (r)) {
            CAN_LAND_ON_PLANET      = true;
        }
        if (dist <= planet_gravity_range + r) {
            attractor               = i;
            IN_GRAVITY_WELL         = true;
        }
    }
    if (ON_PLANET) {
        oxygen = 100.0;
    }
    if (!ON_PLANET) {
        TRAVERSING_PLANET = false;
    }
    if (ON_PLANET && !TRAVERSING_PLANET) {
        TRAVERSING_PLANET       = true;
    }
    if (ON_PLANET && CAN_LAND_ON_PLANET) {
            CAN_LAND_ON_PLANET      = false;
            collisionData(collision);
        }
    if (ON_PLANET && ORIENT_TO_PLANET) {
            orientToPlanet(collision);
            bounce();
        }
    if (IN_GRAVITY_WELL && CAN_LAND_ON_PLANET && USING_GRAVITY) {
            calculateGravity(attractor);
        }
    if (!IN_GRAVITY_WELL) {
        display_g.set(0);
        oxygen -= dt;
        }
}

bool Player::detectCollisions() {  ///Not in use
    for (int i = 0; i < gravitator->size(); i++) {
        float dist = pos.distance((*gravitator)[i]->pos);
        float sum_radii = r + (*gravitator)[i]->r;
        dist -= sum_radii;
    }
}

void Player::collisionData(int collision) {
    planet_pos                          = (*gravitator)[collision]->pos;
    planet_m                            = (*gravitator)[collision]->m;
    planet_r                            = (*gravitator)[collision]->r;
    collision_normal.set(pos - planet_pos);
    normalized_collision_normal         = collision_normal.getNormalized();
    collision_perpendicular             = collision_normal.getPerpendicular();
    left                                = collision_perpendicular;
    right                               = -collision_perpendicular;

    if (!SIMPLE_GRAVITY) {
        maxJump= jump_multiplier * planet_m;
    }
    //cout << ofToString(planet_m) << endl;
}

//void Player::bounce() {
    /*
    float a1 = v.dot(normalized_collision_normal);
    float optimizedP = (2.0 * a1) / (m + planet_m);
    ofVec2f v_prime = v - optimizedP * planet_m * normalized_collision_normal;
    v_prime *= restitution;

    if (!CAN_LAND_ON_PLANET){
        v.set(v_prime);
    }
    */
//}

void Player::calculateGravity(int attractor) {
    ofVec2f planet_pos = (*gravitator)[attractor]->pos;
    int planet_gravity_range = (*gravitator)[attractor]->gR;
    int planet_size =  (*gravitator)[attractor]->r;
    int planet_mass = (*gravitator)[attractor]->m;

    ofVec2f planet_to_player_normal;
    planet_to_player_normal.set(planet_pos - pos);
    ofVec2f sqrDist;
    //sqrDist.set(pos.squareDistance(planet_pos) - (planet_to_player_normal * planet_to_player_normal));
    sqrDist.set(pos.squareDistance(planet_pos));

    /// NOTE (Aaron#5#): Gravity with mass works, but it seems to make everything way too hard.
    if (SIMPLE_GRAVITY) {
    gravity               += G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();
    } else {
    gravity               += G * (m * planet_mass) / (sqrDist) * planet_to_player_normal.normalized();
    }

}

void Player::orientToPlanet(int collision) {
    jumpDir.set(collision_perpendicular.normalized());
}

void Player::traversePlanet(bool move_left) {
    float theta;
    theta = atan2(collision_normal.y / planet_r, collision_normal.x / planet_r);

    if (move_left) {
        theta -= speed_on_planet / planet_r * dt;
    } else {
        theta += speed_on_planet / planet_r * dt;
    }
    pos.x = (cos(theta) * (planet_r + r)) + planet_pos.x;
    pos.y = (sin(theta) * (planet_r + r)) + planet_pos.y;

}

void Player::rotateDirection(bool rotate_left) {
    if (rotate_left) {
        rotation -= rotation_speed;
    } else {
        rotation += rotation_speed;
    }
    dir.set(cos(ofDegToRad(rotation)), sin(ofDegToRad(rotation)));
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
    if (!CAN_LAND_ON_PLANET) {
    f += jumpStrength;
    TRAVERSING_PLANET = false;
    }
    jumpStrength = 0;
}

void Player::jetpack() {
    ofVec2f VEC_MAGNITUDE(jetpack_power, jetpack_power);
    f += VEC_MAGNITUDE;
    oxygen -= jetpack_o2_use;
    cout << "impulsed at " + ofToString(f.x, 0) + "N, " + ofToString(f.y, 0) + "N" + nl;
}

void Player::keyPressed(ofKeyEventArgs& args) {
    /// TODO (Aaron#9#): Determine why player key listener doesn't apply input (it registers key presses)
    switch (args.key) {
    case 'g':
        //USING_GRAVITY = !USING_GRAVITY;
        break;
    }

    if (!ON_PLANET) {
        switch (args.key) {
        case OF_KEY_UP:

            break;
        case OF_KEY_LEFT:

            break;
        case OF_KEY_RIGHT:

            break;
        case OF_KEY_DOWN:

            cout << "impulsed at " + nl;

            break;
        case 32:
            chargeJump();
            break;
        }
    }
}

void Player::keyReleased(ofKeyEventArgs& args) {

}
