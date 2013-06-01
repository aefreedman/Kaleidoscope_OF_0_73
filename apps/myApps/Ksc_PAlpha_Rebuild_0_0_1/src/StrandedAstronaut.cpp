#include "StrandedAstronaut.h"
#include "Message.h"
#define dt 1.0/60.0
#define nl "\n"

StrandedAstronaut::StrandedAstronaut() : Astronaut() {
    //ctor
}

StrandedAstronaut::StrandedAstronaut(ofVec2f _pos, name _name, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut) : Astronaut(_pos), gravitator(gravitator), strandedAstronaut(strandedAstronaut) {
    pos                         = _pos;
    r                           = 20;
    m                           = 5.0;
    rotation                    = 180;
    damp                        = 1.0;
    restitution                 = 0.5;
    oxygen                      = 100;

    if (_name == UNNAMED) {
        message_timer               = ofRandom(0.0, 10.0);      ///Increase this to decrease the time to see first message (if higher than message_delay, will auto-display message)
        message_delay               = 15;                       ///Minimum delay between messages
        message_display_chance      = 7;                        ///larger number makes random delay between messages higher
    } else {
        message_timer           = ofRandom(0.0, 5.0);
        message_delay           = 10;
        message_display_chance  = 3;
    }
    lerp_speed                  = 0.15;
    astronaut_pickup_range      = 30;
    spring_strength             = 15000;
    astronaut                   = 0;
    astronaut_drop_range        = 200;
    spring_spacing              = 0;
    no_spacing                  = 0;
    released_spacing            = 40;
    v_limit_in_space            = 600;
    v_limit                     = v_limit_in_space;
    v_limit_in_gravity          = 4 * v_limit_in_space;
    release_timer_start         = 2.0;
    release_timer               = release_timer_start;

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
    CAN_TALK                    = true;
    DRAW_MESSAGE                = false;
    DYING                       = false;
    IS_DEAD                     = false;
    GHOSTLY                     = false;
    THE_END                     = false;
    CAN_HIT_ASTRONAUTS          = false;
    RELEASED                    = false;
    CHECKED_DEAD                = false;

    type = "strandedastronaut";
    anim = floating;
    flameAnim = nautFire;

	ofEnableAlphaBlending();
	setName(_name);
	loadMessages();
	dialogueBubble = new Message(pos, "");
}

StrandedAstronaut::~StrandedAstronaut() {
}

void StrandedAstronaut::loadMessages() {
    ofxXmlSettings dialogue;
    message.clear();
    if (dialogue.loadFile("data/messages/dialogue.xml")) {
        dialogue.pushTag("dialogue");
            dialogue.pushTag("ENUM_" + ofToString(thisAstronautIs));
                int numberOfMessages = dialogue.getNumTags("message");
                for (int i = 0; i < numberOfMessages; i++) {
                    string m = dialogue.getValue("message", "", i);
                    message.push_back(m);
                }
            dialogue.popTag();
            dialogue.pushTag("ENUM_5");
                numberOfMessages = dialogue.getNumTags("message");
                for (int i = 0; i < numberOfMessages; i++) {
                    string m = dialogue.getValue("message", "", i);
                    message.push_back(m);
                }
            dialogue.popTag();
        dialogue.popTag();
    }
    else {
        ofLogError("Dialogue file did not load!");
    }
}

void StrandedAstronaut::update() {
    checkState();
    detectPlayerCollisions();
    detectGravitatorCollisions();
    move();
    DRAW_MESSAGE = displayMessageTimer();
    if (DRAW_MESSAGE) {
        displayMessage();
    }
    dialogueBubble->update();

    if (anim.index == 14 && anim.frame >= 11){
        IS_DEAD = true;
        DYING = false;
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
        v.interpolate(v.getScaled(v_limit), 4 * dt);
    }

    v *= damp;
    pos += v * dt;
    dialogueBubble->pos.set((pos + ofVec2f(10, -35)));

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
    if (IN_GRAVITY_WELL) {
        v_limit = v_limit_in_gravity;
    } else {
        v_limit = v_limit_in_space;
    }
    if (FOLLOWING_ASTRONAUT) {
        getPlayerData((*strandedAstronaut)[astronaut]->pos, (*strandedAstronaut)[astronaut]->v);
        if (!(*strandedAstronaut)[astronaut]->RELEASED) {
        }
    }
    if (FOLLOWING_PLAYER) {
    }
    if (FOLLOWING_ASTRONAUT || FOLLOWING_PLAYER) {
        //CAN_HIT_ASTRONAUTS = false;
        damp = 0.93;
    }  else {
        damp = 1.0;
    }
    if (RELEASED) {
        //spring_spacing = released_spacing;
        spring_strength = 1000;
        release_timer = countdownTimer(release_timer);
        if (release_timer <= 0) {
            followReset();
        }
    } else if (!RELEASED) {
        spring_strength = 15000;
        spring_spacing = no_spacing;
        release_timer = release_timer_start;
    }
}

void StrandedAstronaut::followReset() {
    FOLLOWING_ASTRONAUT         = false;
    FOLLOWING_PLAYER            = false;
    RELEASED                    = false;
    release_timer               = release_timer_start;
    spring_spacing              = no_spacing;
}

void StrandedAstronaut::displayMessage() {
    string _message = pickMessageRandom();
    dialogueBubble->changeMessage(_message);
    DRAW_MESSAGE = false;
}

void StrandedAstronaut::displayMessage(int messageNumber) {
    string _message = pickMessage(messageNumber);
    dialogueBubble->changeMessage(_message);
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
    int messageNumber = ofRandom(message.size());
    string m = message[messageNumber];
    return m;
}

string StrandedAstronaut::pickMessage(int messageNumber) {
    string m = message[messageNumber];
    return m;
}

void StrandedAstronaut::draw(float scale) {
    //ofScale(scale, scale, 1);
    if (!IS_DEAD) {
        if (FOLLOWING_PLAYER || FOLLOWING_ASTRONAUT) {
            ofPushMatrix();
            ofNoFill();
            ofSetColor(240, 206, 103, 200);
            int d = 4;
            int offset = 2;
            ofBezier(player_pos.x, player_pos.y, player_pos.x, player_pos.y, pos.x + (v.x / d), pos.y + (v.y / d), pos.x, pos.y);
            ofBezier(player_pos.x, player_pos.y, player_pos.x + (-player_v.x / d), player_pos.y + (-player_v.y / d), pos.x, pos.y, pos.x, pos.y);
            ofPopMatrix();
        }
        dialogueBubble->draw(scale, 255);
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
                if (dist < collision_range - (r/2)) {
                    float theta;
                    theta = atan2(collision_normal.y / planet_r, collision_normal.x / planet_r);
                    pos.x = (cos(theta) * (planet_r + r)) + planet_pos.x;
                    pos.y = (sin(theta) * (planet_r + r)) + planet_pos.y;
                }
            }
            if ((gravitator_type == "sun" || gravitator_type == "comet") && DYING == false) {
                DYING = true;
                anim = nautDeath;
            }
            if (gravitator_type == "blackhole") {

            }
            HIT_GRAVITATOR          = true;
        }
        if (dist > collision_range) {
            HIT_GRAVITATOR = false;
        }
        if (dist < gravity_range && USING_GRAVITY && !HIT_GRAVITATOR) {
            gravity               += planet_G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();
        }
    }
}

void StrandedAstronaut::gravitatorBounce() {
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

void StrandedAstronaut::followPlayer(ofVec2f _player_pos) {
    ofVec2f normal;
    normal.set(pos - _player_pos);
    if (normal.length() < spring_spacing) {
        f += k * (normal);
    } else {
        f += -k * (normal);
    }
}

void StrandedAstronaut::getPlayerData(ofVec2f _other_pos, ofVec2f _other_v) {
    player_pos = _other_pos;
    player_v = _other_v;
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
                ofVec2f normal;
                normal.set(pos - other_pos);
                if (CAN_HIT_ASTRONAUTS) {
                    bounce(i);
                    if (dist < collision_range) {
                        float theta;
                        theta = atan2(normal.y / planet_r, normal.x / other_r);
                        pos.x = (cos(theta) * (other_r + r)) + other_pos.x;
                        pos.y = (sin(theta) * (other_r + r)) + other_pos.y;
                    }
                }
            }
            if (dist < pickup_range) {
                if (FOLLOWING_PLAYER) {

                } else if (!FOLLOWING_PLAYER) {
                    if (FOLLOWING_ASTRONAUT) {

                    }
                    if (!FOLLOWING_ASTRONAUT && (*strandedAstronaut)[i]->THE_END) {
                        (*strandedAstronaut)[i]->THE_END = false;
                        THE_END = true;
                        astronaut = i;
                        FOLLOWING_ASTRONAUT = true;
                        getPlayerData((*strandedAstronaut)[astronaut]->pos, (*strandedAstronaut)[astronaut]->v);
                    }
                }
            }
        }
    }
}
