#include "StrandedAstronaut.h"
#include "Message.h"
#define dt 1.0/60.0
#define nl "\n"

StrandedAstronaut::StrandedAstronaut() : Astronaut() {
    //ctor
}

StrandedAstronaut::StrandedAstronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut, std::vector<GUI *> *gui) : Astronaut(_pos), gravitator(gravitator), strandedAstronaut(strandedAstronaut), gui(gui) {
    pos                         = _pos;
    r                           = 20;
    m                           = 0.5;
    rotation                    = 180;
    damp                        = 0.97;
    restitution                 = 0.5;
    oxygen                      = 100;
    message_timer               = ofRandom(0.0, 15.0);      ///Increase this to decrease the time to see first message (if higher than message_delay, will auto-display message)
    message_delay               = 20;                       ///Minimum delay between messages
    message_display_chance      = 7;                        ///larger number makes random delay between messages higher
    lerp_speed                  = 0.15;
    astronaut_pickup_range      = 30;
    spring_strength             = 3000;
    astronaut                   = 0;
    astronaut_drop_range        = 200;
    spring_spacing              = 40;
    v_limit                     = 600.0;

    a.set(0, 0);
    f.set(0, 0);
    dir.set(-1, 0);
    k.set(spring_strength, spring_strength);

    FOLLOWING_PLAYER            = false;
    FOLLOWING_ASTRONAUT         = false;
    HIT_GRAVITATOR              = false;
    IN_GRAVITY_WELL             = false;
    EXITED_GRAVITY_WELL         = false;
    ORIENT_TO_PLANET            = true;
    USING_GRAVITY               = true;
    SIMPLE_GRAVITY              = true;
    CAN_TALK                    = true;
    DRAW_MESSAGE                = false;
    IS_DEAD                     = false;
    THE_END                     = false;

    type = "strandedastronaut";


    anim = floating;

	ofEnableAlphaBlending();
}

StrandedAstronaut::~StrandedAstronaut() {
}

/// TODO (Aaron#1#): Astronauts should sit and wait for the player, then follow the player when the player gets close enough to it
void StrandedAstronaut::update() {
    checkState();
    detectPlayerCollisions();
    detectGravitatorCollisions();
    move();
    DRAW_MESSAGE = displayMessageTimer();
    if (DRAW_MESSAGE) {
        displayMessage();
    }
}

void StrandedAstronaut::move() {
    if (FOLLOWING_PLAYER) {
        followPlayer(player_pos);
    }
    if (FOLLOWING_ASTRONAUT) {
        followPlayer((*strandedAstronaut)[astronaut]->pos);
    }

    a  = (f / m) * dt;
    //v += dir * a * dt;
    v += a * dt;
    v += gravity * dt;
    if (v.length() > v_limit) {
        v.scale(v_limit);
    }

    v *= damp;
    pos += v * dt;

    f.set(0, 0);
    gravity.set(0, 0);
}

void StrandedAstronaut::bounce(int other) {
    ofVec2f other_pos = (*strandedAstronaut)[other]->pos;
    ofVec2f other_v = (*strandedAstronaut)[other]->v;
    float other_mass = (*strandedAstronaut)[other]->m;
    ofVec2f sa_normal = pos - other_pos;
    sa_normal.normalize();
    float a1 = v.dot(sa_normal);
    float a2 = other_v.dot(sa_normal);
    float optimizedP = (2.0 * (a1 - a2)) / (m + other_mass);

    ofVec2f v1_prime = v - optimizedP * other_mass * sa_normal;
    ofVec2f v2_prime = other_v + optimizedP * m * sa_normal;

    v.set(v1_prime * restitution);
    (*strandedAstronaut)[other]->v.set(v2_prime * restitution);
}

void StrandedAstronaut::checkState() {
    if (HIT_GRAVITATOR) {
    }
    if (!HIT_GRAVITATOR) {
    }
    if (HIT_GRAVITATOR && ORIENT_TO_PLANET) {
    }
    if (IN_GRAVITY_WELL && USING_GRAVITY) {
    }
    if (!IN_GRAVITY_WELL) {
    }
    if (FOLLOWING_ASTRONAUT) {
        getPlayerData((*strandedAstronaut)[astronaut]->pos);
    }
}

void StrandedAstronaut::displayMessage() {
    string message = pickMessageRandom();
    (*gui).push_back(new Message(pos + ofVec2f(0, -15), message));
    DRAW_MESSAGE = false;
}

void StrandedAstronaut::displayMessage(int messageNumber) {
    string message = pickMessage(messageNumber);
    (*gui).push_back(new Message(pos + ofVec2f(0, -15), message));
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
}

string StrandedAstronaut::pickMessageRandom() {
    int messageNumber = ofRandom(13);
    string message = pickMessage(messageNumber);
    return message;
}

string StrandedAstronaut::pickMessage(int messageNumber) {
    string message = "";
    switch (messageNumber) {
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
    /*
    ofNoFill();
    ofSetColor(255, 255, 255);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(rotation,0, 0, 1);
    ofPopMatrix();
    */

    if (FOLLOWING_PLAYER || FOLLOWING_ASTRONAUT) {
        ofPushMatrix();
        ofSetColor(255, 0, 0, 200);
        ofLine(pos, player_pos);
        ofPopMatrix();
    }
}

void StrandedAstronaut::detectGravitatorCollisions() {
    for (int i = 0; i < gravitator->size(); i++) {
        ofVec2f planet_pos          = (*gravitator)[i]->pos;
        float dist                  = pos.squareDistance((*gravitator)[i]->pos);
        string gravitator_type      = (*gravitator)[i]->type;
        int planet_r                = (*gravitator)[i]->r;
        int planet_gravity_range    = (*gravitator)[i]->gR;
        int planet_mass             = (*gravitator)[i]->m;
        float planet_G              = (*gravitator)[i]->G;
        ofVec2f planet_to_player_normal;
        planet_to_player_normal.set(planet_pos - pos);
        float collision_range       = (planet_r + r) * (planet_r + r);
        float gravity_range         = (planet_gravity_range + r) * (planet_gravity_range + r);

        if (dist <= collision_range) {
            collision               = i;
            collisionData(i);
            if (gravitator_type == "planet") {
                gravitatorBounce();
            }
           if (gravitator_type != "planet") {
                IS_DEAD = true;
            }
            HIT_GRAVITATOR          = true;
        }
        if (dist > collision_range) {

        }
        if (dist < gravity_range && USING_GRAVITY) {
            if (SIMPLE_GRAVITY) {
                gravity               += planet_G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();
            } else {
                gravity               += planet_G * (m * planet_mass) / (dist) * planet_to_player_normal.normalized();
            }
        }
    }
}

void StrandedAstronaut::gravitatorBounce() {
    if (v.length() < 0.05) {
        //v.set(0, 0);
    }
    float a1 = v.dot(normalized_collision_normal);
    float optimizedP = (2.0 * a1) / (m + planet_m);
    ofVec2f v_prime = v - optimizedP * planet_m * normalized_collision_normal;
    v_prime *= restitution;
    v.set(v_prime);
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
    gravitator_type                     = (*gravitator)[collision]->type;
}

void StrandedAstronaut::orientToPlanet(int collision) {

}

void StrandedAstronaut::followPlayer() {
    float randomized_speed = ofRandom(lerp_speed * 0.95, lerp_speed * 1.05);
    float dist = pos.squareDistance(player_pos);
    if (dist > (20 * 20)){
    //pos.interpolate(player_pos, lerp_speed);
    //v = player_v;
    }
}

void StrandedAstronaut::followPlayer(ofVec2f _player_pos) {
    ofVec2f normal;
    normal.set(pos - _player_pos);
    if (normal.length() < spring_spacing) {
        f += k * (normal);
    } else {
        f += -k * (normal);
    }
}

void StrandedAstronaut::getPlayerData(ofVec2f _other_pos) {
    player_pos = _other_pos;
}

void StrandedAstronaut::detectPlayerCollisions() {
    for (int i = 0; i < strandedAstronaut->size(); i++) {
            ofVec2f other_pos;
            other_pos               = (*strandedAstronaut)[i]->pos;
            float dist              = pos.squareDistance(other_pos);
            if (dist > 0) {
                float other_r           = (*strandedAstronaut)[i]->r;
                float pickup_range      = (r + other_r + astronaut_pickup_range) * (r + other_r + astronaut_pickup_range);
                float drop_range        = (r + other_r + astronaut_drop_range) * (r + other_r + astronaut_drop_range);
                float collision_range   = (r + other_r) * (r + other_r);
            if (dist < collision_range) {
                bounce(i);
            }
            if (dist < pickup_range) {
                if (FOLLOWING_PLAYER) {

                } else if (!FOLLOWING_PLAYER) {
                    if (FOLLOWING_ASTRONAUT) {

                    }
                    if (!FOLLOWING_ASTRONAUT && (*strandedAstronaut)[i]->THE_END) {
                        (*strandedAstronaut)[i]->THE_END = false;
                        THE_END = true;
                        FOLLOWING_ASTRONAUT = true;
                        astronaut = i;
                    }
                }
            }
        }
    }
}
