#include "StrandedAstronaut.h"
#include "Message.h"
#define dt 1.0/60.0
#define nl "\n"

StrandedAstronaut::StrandedAstronaut() : Astronaut() {
    //ctor
}

StrandedAstronaut::StrandedAstronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<GUI *> *gui) : Astronaut(_pos), gravitator(gravitator), gui(gui) {
    pos                         = _pos;
    r                           = 5;
    m                           = 1.0;
    G                           = 9.8;
    rotation                    = 180;
    damp                        = 1.0;
    restitution                 = 0.0;
    oxygen                      = 100;
    message_timer               = 0.0;      ///Increase this to decrease the time to see first message (if higher than message_delay, will auto-display message)
    message_delay               = 7;        ///Minimum delay between messages
    message_display_chance      = 5;        ///larger number makes random delay between messages higher


    a.set(0, 0);
    f.set(0, 0);
    dir.set(-1, 0);

    FOLLOWING_PLAYER            = false;
    ON_PLANET                   = false;
    IN_GRAVITY_WELL             = false;
    EXITED_GRAVITY_WELL         = false;
    ORIENT_TO_PLANET            = true;
    USING_GRAVITY               = true;
    SIMPLE_GRAVITY              = true;
    CAN_LAND_ON_PLANET          = true;
    CAN_TALK                    = true;
    DRAW_MESSAGE                = false;
}

StrandedAstronaut::~StrandedAstronaut() {
    //dtor
}

/// TODO (Aaron#1#): Astronauts should sit and wait for the player, then follow the player when the player gets close enough to it
void StrandedAstronaut::update() {
    detectPlayerCollisions();
    detectGravitatorCollisions();
    move();
    DRAW_MESSAGE = displayMessageTimer();
    if (DRAW_MESSAGE) {
        displayMessage();
    }
}

void StrandedAstronaut::displayMessage() {
    string message = pickMessage();
    (*gui).push_back(new Message(pos, message));
    DRAW_MESSAGE = false;
}

bool StrandedAstronaut::displayMessageTimer() {
    message_timer += dt;

    if (message_timer >= message_delay) {
        message_dieroll = ofRandom(message_display_chance);
        if (message_dieroll = message_display_chance) {
            message_timer = 0;
            return true;
        }
    } else return false;
    cout << "Timer: " + ofToString(message_timer) + "DM: " + ofToString(DRAW_MESSAGE) << endl;
}

string StrandedAstronaut::pickMessage() {
    int which_message = ofRandom(13);
    string message = "";

    switch (which_message) {
        case 0:
        message = "Hello there!";
        break;
        case 1:
        message = "Oh no!";
        break;
        case 2:
        message += "Well, this isn't exactly \n";
        message += "what I would call a vacation.";
        break;
        case 3:
        message = "Could you help me out, please?";
        break;
        case 4:
        message = "Don't leave me.";
        break;
        case 5:
        message = "I hate space.";
        break;
        case 6:
        message = "Why am I still floating?";
        break;
        case 7:
        message = "I hope I can float my way to a bathroom...";
        break;
        case 8:
        message = "WHY DID YOU LET ME GO?!";
        break;
        case 9:
        message = "Oops.";
        break;
        case 10:
        message = "Guys...";
        break;
        case 11:
        message += "If a tree falls in \n";
        message += "space can you hear it?";
        break;
        case 12:
        message = "Can we talk for a moment?";
        break;
        case 13:
        message = "Hey.";
        break;


    }
    return message;
}

void StrandedAstronaut::draw() {

    ofNoFill();
    ofSetColor(100, 100, 100);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(rotation,0, 0, 1);
    ofCircle(0, 0, r);
    //ofRect(-5, -5, w, h);
    //ofRect(-2.5, 5, w/2, h/2);
    ofLine(ofPoint(0, 0), ofPoint(100, 0));
    ofPopMatrix();


}

void StrandedAstronaut::move() {
    if (FOLLOWING_PLAYER) {
        followPlayer();
    }

    a  = (f / m) * dt;
    v += dir * a * dt;
    v += dir * dt;
    v += gravity * dt;
    v *= damp;
    pos += v * dt;

    f.set(0, 0);
    gravity.set(0, 0);
}

void StrandedAstronaut::detectGravitatorCollisions() {
    ON_PLANET = false;
    IN_GRAVITY_WELL = false;
    EXITED_GRAVITY_WELL = false;

    for (int i = 0; i < gravitator->size(); i++) {
        float dist                = pos.distance((*gravitator)[i]->pos);
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
    if (ON_PLANET) {
        oxygen = 100.0;
        collisionData(collision);
    }
    if (ON_PLANET && CAN_LAND_ON_PLANET) {
        CAN_LAND_ON_PLANET = false;
    }
    if (ON_PLANET && ORIENT_TO_PLANET) {
        orientToPlanet(collision);
        bounce();
    }
    if (IN_GRAVITY_WELL && CAN_LAND_ON_PLANET && USING_GRAVITY) {
        calculateGravity(attractor);
    }
    if (!IN_GRAVITY_WELL) {
        //display_g.set(0);
        oxygen -= dt;
    }

}

void StrandedAstronaut::collisionData(int collision) {
    planet_pos                          = (*gravitator)[collision]->pos;
    planet_m                            = (*gravitator)[collision]->m;
    planet_r                            = (*gravitator)[collision]->r;
    collision_normal.set(pos - planet_pos);
    normalized_collision_normal         = collision_normal.getNormalized();
    collision_perpendicular             = collision_normal.getPerpendicular();
    left                                = collision_perpendicular;
    right                               = -collision_perpendicular;
}

//void StrandedAstronaut::bounce() {
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

void StrandedAstronaut::calculateGravity(int attractor) {
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
    //display_g.set(gravity);
}

void StrandedAstronaut::orientToPlanet(int collision) {

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
