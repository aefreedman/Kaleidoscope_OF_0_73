#include "Player.h"
#define fps 60
#define dt 1.0/60.0

Player::Player() : Astronaut() {
    //ctor
}

Player::~Player() {

}

Player::Player(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut,  std::vector<GUI *> *gui) : Astronaut(_pos), gravitator(gravitator), strandedAstronaut(strandedAstronaut), gui(gui) {
    setup();
    pos.set(500,500);
    starting_pos.set(pos);

    p1Renderer = new ofxSpriteSheetRenderer(1, 10000, 0, 32);               /// declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 64
    p1Renderer->loadTexture("ART/playerSheet2.png", 384, GL_NEAREST);           /// load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    //ofRegisterKeyEvents(this);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyPressed);
    //ofAddListener(ofEvents().keyPressed, this, &Player::keyReleased);

    DEBUG_GUI = false;
}

void Player::setup() {
    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------

    rotation                = 180;
    camera_timer            = 0;
    attractor               = 0;
    astronaut_pickup_delay  = 1.0;
    astronaut_release_timer = astronaut_pickup_delay;

    f.set(0,0);
    v.set(0,0);
    dir.set(-1, 0);
    pos.set(starting_pos);

    IS_DEAD                 = false;
    HIT_GRAVITATOR          = false;
    TRAVERSE_MODE           = false;
    USING_GRAVITY           = true;
    ORIENT_TO_PLANET        = true;
    CAN_JETPACK             = true;
    LEAVING_PLANET          = false;
    DEATH_ANIMATION         = false;
    JETPACK_EMPTY           = false;
    FACING_RIGHT            = true;
    ROTATE_LEFT             = false;
    ROTATE_RIGHT            = false;
    HAVE_ASTRONAUT          = false;
    OFF_SCREEN_CHECK        = true;
    SIMPLE_GRAVITY          = true;

    p1Renderer = new ofxSpriteSheetRenderer(1, 10000, 0, 32);               /// declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 64
	p1Renderer->loadTexture("ART/playerSheet2.png", 384, GL_NEAREST);           /// load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    gravitator_type         = "null";
    anim = idle;
    ofEnableAlphaBlending();
    releaseAllAstronauts(false);
    ///------------------------------
    /// YOU CAN CHANGE THESE
    ///------------------------------

    w                       = 10;
    h                       = 10;
    r                       = 10;
    oxygen                  = 100.0;        /// TODO (Aaron#1#): Add lose condition to running out of o2
    max_oxygen              = oxygen;
    damp                    = 1.00;
    m                       = 1.0;
    jumpStrength            = 0.0;
    jump_strength_1         = 500000.0;
    jump_strength_2         = 1000000.0;
    jump_strength_3         = 2000000.0;
    restitution             = 0.50;         /// Used to calculate the amount of momentum conserved when bouncing off a planet
    off_screen_limit        = 0;           /// If this is too large & camera moves by whole screens, camera will freak out
    rotation_speed          = 4.0;          /// This is the speed of your rotation in space
    speed_on_planet         = 150.0;
    jetpack_power           = 8.0 * 100000.0;
    jump_multiplier         = 30.0;
    jetpack_o2_use          = (max_oxygen / 8) - 1;
    astronaut_pickup_range  = 50;
    astronaut_drop_range    = 200;
    planet_orientation_speed= 50.0;
    oxygen_depletion_speed  = 7.0;
    camera_move_delay       = 0.25;
    death_timer             = 0.5;
    flame_rotation          = 0;
    v_limit_in_space        = 300.0;
    v_limit_in_gravity      = 4.0 * v_limit_in_space;
    v_limit                 = 300.0;

    GOD_MODE                = false;
    CAN_HIT_ASTRONAUTS      = false;         /// Bouncing off astronauts gets a little annoying when they keep pushing themselves into you

}

void Player::loadSound() {
    fxDeath.loadSound("AUDIO/ksc_AUDIO_animation_explosion_002.wav");
    fxJetpackEmpty.loadSound("AUDIO/ksc_AUDIO_player_jetout_001.wav");
    fxJetpackUse.loadSound("AUDIO/ksc_AUDIO_player_usejet_004.wav");
    fxRotate.loadSound("AUDIO/ksc_AUDIO_player_usejet_002.wav");
    fxAstronautCollect.loadSound("AUDIO/ksc_AUDIO_astro_pickup_001.wav");
    fxAstronautRelease.loadSound("AUDIO/ksc_AUDIO_astronaut_death_001.wav");
    fxWalk.loadSound("AUDIO/ksc_AUDIO_player_walk_002.wav");
    fxJetpackLoop.loadSound("AUDIO/ksc_AUDIO_player_jetloop_002.wav");
    fxJetpackLoop.setLoop(true);

//    for (int i = 0; i < 3; i++) {
//        fxJump.push_back(ofSoundPlayer());
//        fxJump[i].loadSound("AUDIO/ksc_AUDIO_player_jump_00" + ofToString(i) + ".wav");
//        fxJump[i].setVolume(0.3);
//    }
    //fxJump[0]->loadSound("AUDIO/ksc_AUDIO_jump_001.wav");
    //fxJump[1]->loadSound("AUDIO/ksc_AUDIO_jump_002.wav");
    //fxJump[2]->loadSound("AUDIO/ksc_AUDIO_jump_003.wav");
    //fxJump[3]->loadSound("AUDIO/ksc_AUDIO_jump_004.wav");

    int random = ofRandom (1, 4);
    if (random == 1) {    fxJump.loadSound("AUDIO/ksc_AUDIO_player_jump_001.wav");}
    if (random == 2) {    fxJump.loadSound("AUDIO/ksc_AUDIO_player_jump_002.wav");}
    if (random == 3) {    fxJump.loadSound("AUDIO/ksc_AUDIO_player_jump_003.wav");}
    if (random == 4) {    fxJump.loadSound("AUDIO/ksc_AUDIO_player_jump_004.wav");}

    fxJump.setVolume(0.3);


    fxDeath.setVolume(0.75);

    fxJetpackUse.setVolume(.55);
    fxAstronautCollect.setVolume(.75);
    fxAstronautRelease.setVolume(.75);
    fxRotate.setVolume(0.1);

    fxJetpackUse.setMultiPlay(true);
}

void Player::update() {
    checkState();
    detectGravitatorCollisions();
    detectAstronautCollisions();
    display_g.set(gravity);
    move();

    if (OFF_SCREEN_CHECK) {
        OFF_SCREEN = checkOffScreen();
    }

    p1Renderer->clear(); // clear the sheet
    p1Renderer->update(ofGetElapsedTimeMillis());

    float player_rotation = rotation + 90;
    if (player_rotation >= 360) {
        player_rotation -= 360;
    }
    if (player_rotation <= 0) {
        player_rotation += 360;
    }
    if(DEATH_ANIMATION) {
        //flame_rotation = (-1*v).angle(ofVec2f(0,-1));
        //cout << ofToString(flame_rotation) + "/n";
        p1Renderer->addCenterRotatedTile(&flame, pos.x, pos.y,-1, F_NONE, 2.0, flame_rotation, NULL, 255, 255, 255, 255);
    }

    if(FACING_RIGHT) {
        p1Renderer->addCenterRotatedTile(&anim, pos.x, pos.y,-1, F_HORIZ, 2.0, player_rotation, NULL, 255, 255, 255, 255);
    } else {
        p1Renderer->addCenterRotatedTile(&anim, pos.x, pos.y,-1, F_NONE, 2.0, player_rotation, NULL, 255, 255, 255, 255);
    }
}

void Player::move() {
    if (rotation >= 360 || rotation <= -360) {
        rotation = 0;
    }
    a           = (f / m) * dt;
    v          += dir * a * dt;
    v          += gravity * dt;
    v          *= damp;
    if (v.length() > v_limit) {
        //v.set(v.getScaled(v_limit));
        v.interpolate(v.getScaled(v_limit), 4 * dt);
    }
    pos        += v * dt;

    display_f   = m / a;
    f.set(0, 0);
    gravity.set(0, 0);

    if (DEBUG_GUI) {
        cout << "v(" + ofToString(v.x, 3) + ", " + ofToString(v.y, 3) + ")" + "   ";
        cout << "Pos(" + ofToString(pos.x, 3) + ", " + ofToString(pos.y, 3) + ")" << endl;
    }
}

void Player::draw() {
    ofSetColor(0, 255, 240);
    ofFill();
    ofPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(rotation,0, 0, 1);
    //ofCircle(0, 0, r);
    //ofLine(ofPoint(0, 0), ofPoint(50, 0));
    ofPopMatrix();

    drawGUI();

    if (DEBUG_GUI) {
        drawDebugGUI();
    }

    p1Renderer->draw();
}

void Player::drawGUI() {

}

void Player::drawDebugGUI() {
    int x = (30 + camera_pos.x);
    int y = (550 + camera_pos.y);
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
    info += "maxJump: " + ofToString(jump_strength_3, 2) + nl;

    ofSetColor(240, 0, 20);
    ofDrawBitmapString(info, x, y);

    string info_b = "";
    if (HIT_GRAVITATOR) {
        info_b.append("ON THE PLANET, BRO \n");
    }
    if (IN_GRAVITY_WELL) {
        info_b.append("IN THE GRAVITY WELL, BRO \n");
    }
    else {
        info_b.append("LANDED ON THE PLANET, BRO \n");
    }
    ofSetColor(240, 0, 20);
    ofDrawBitmapString(info_b, x + column_width, y);
}

void Player::checkState() {
    ///---------------------
    /// CHEATS
    ///---------------------
    if (GOD_MODE) {
        oxygen = max_oxygen;
    }

    ///---------------------
    /// DEATH
    ///---------------------
    if (oxygen < 0) {
        DEATH_ANIMATION = die();
    }
    if (gravitator_type == "sun" || gravitator_type == "comet") {
        DEATH_ANIMATION = die();
    }
    if (OFF_SCREEN) {
        //DEATH_ANIMATION = die();
    }

    ///---------------------
    /// ABILITIES
    ///---------------------
    if (JETPACK_EMPTY) {

    }
    if (DEATH_ANIMATION) {

    }
    if (!TRAVERSE_MODE) {
        USING_GRAVITY = true;
        HIT_GRAVITATOR = false;
        if (ROTATE_LEFT) {
            rotateDirection(true);
        }
        if (ROTATE_RIGHT) {
            rotateDirection(false);
        }
    } else if (TRAVERSE_MODE) {
        if (ROTATE_LEFT) {
            traversePlanet(true);
        }
        if (ROTATE_RIGHT) {
            traversePlanet(false);
        }
    }
    if (!CAN_PICKUP_ASTRONAUTS) {
        astronaut_release_timer = countdownTimer(astronaut_release_timer);
        if (astronaut_release_timer <= 0) {
            CAN_PICKUP_ASTRONAUTS = true;
        }
    } else if (CAN_PICKUP_ASTRONAUTS) {
        astronaut_release_timer = astronaut_pickup_delay;
    }

    ///---------------------
    /// GRAVITATORS
    ///---------------------
    if (TRAVERSE_MODE) {
        if (gravitator_type == "planet") {
            if (oxygen < max_oxygen) {
            oxygen          += 5 * oxygen_depletion_speed * dt;
            }
        }
    } else if (!TRAVERSE_MODE) {
    }
    if (IN_GRAVITY_WELL) {
        v_limit = v_limit_in_gravity;
        if (gravity_type == "planet") {
            if (oxygen < max_oxygen) {
            oxygen          += 1 * oxygen_depletion_speed * dt;
            }
        } else if (gravity_type != "planet") {
            if (oxygen > 0) {
                oxygen                     -= oxygen_depletion_speed * dt;
            }
        }
    } else if (!IN_GRAVITY_WELL) {
        v_limit = v_limit_in_space;
        oxygen                     -= oxygen_depletion_speed * dt;
    }
    if (LEAVING_PLANET) {
        jump_timer -= dt;
        if (jump_timer < 0) {
            LEAVING_PLANET = false;
            TRAVERSE_MODE = false;
        }
    }
    if (HIT_GRAVITATOR && ORIENT_TO_PLANET) {
    }
    if (!IN_GRAVITY_WELL) {
        display_g.set(0);
    }
}

bool Player::checkOffScreen() {
    if (camera_timer > 0) {
        camera_timer -= dt;
    }
    if (camera_timer <= 0) {
        if (pos.x > camera_target.x + ofGetWidth() - off_screen_limit) {
            camera_move_direction = "right";
            camera_timer = camera_move_delay;
            return true;
        }
        if (pos.x < camera_target.x + off_screen_limit) {
            camera_move_direction = "left";
            camera_timer = camera_move_delay;
            return true;
        }
        if (pos.y > camera_target.y + ofGetHeight() - off_screen_limit) {
            camera_move_direction = "down";
            camera_timer = camera_move_delay;
            return true;
        }
        if (pos.y < camera_target.y + off_screen_limit) {
            camera_move_direction = "up";
            camera_timer = camera_move_delay;
            return true;
        } else return false;
    } else return false;
}

void Player::soundPlayer(string sound) {
    if (sound == "death") {

    }
}

void Player::detectAstronautCollisions() {
    for (int i = 0; i < strandedAstronaut->size(); i++) {
        float dist                  = pos.squareDistance((*strandedAstronaut)[i]->pos);
        float astronaut_r           = (*strandedAstronaut)[i]->r;
        float pickup_range          = (astronaut_pickup_range) * (astronaut_pickup_range) + (20 * 20);
        float collision_range       = (r + astronaut_r) * (r + astronaut_r);
        //float pickup_range          = (r + astronaut_r + astronaut_pickup_range) * (r + astronaut_r + astronaut_pickup_range);
        float drop_range            = (astronaut_drop_range) * (astronaut_drop_range);
        bool ANAUT_IS_FOLLOWING_ME  = (*strandedAstronaut)[i]->FOLLOWING_PLAYER;

        if (dist <= collision_range && CAN_HIT_ASTRONAUTS) {
            ofVec2f other_pos = (*strandedAstronaut)[i]->pos;
            ofVec2f other_v = (*strandedAstronaut)[i]->v;
            float other_mass = (*strandedAstronaut)[i]->m;
            float other_restitution = (*strandedAstronaut)[i]->restitution;
            ofVec2f sa_normal = pos - other_pos;
            sa_normal.normalize();
            float a1 = v.dot(sa_normal);
            float a2 = other_v.dot(sa_normal);
            float optimizedP = (2.0 * (a1 - a2)) / (m + other_mass);

            ofVec2f v1_prime = v - optimizedP * other_mass * sa_normal;
            ofVec2f v2_prime = other_v + optimizedP * m * sa_normal;

            v.set(v1_prime * restitution);
            (*strandedAstronaut)[i]->v.set(v2_prime * other_restitution);
        }
        if (CAN_PICKUP_ASTRONAUTS) {
            if (!HAVE_ASTRONAUT && !(*strandedAstronaut)[i]->FOLLOWING_PLAYER && dist <= pickup_range) {
                (*strandedAstronaut)[i]->FOLLOWING_PLAYER               = true;
                (*strandedAstronaut)[i]->THE_END                        = true;
                (*strandedAstronaut)[i]->RELEASED                       = false;
                HAVE_ASTRONAUT                                          = true;
                fxAstronautCollect.play();
                if (DEBUG_GUI) {
                    cout << "I'm Astronaut #" + ofToString(i) + " and I'm following you!" << endl;
                }
            }
//            if (dist > drop_range && (*strandedAstronaut)[i]->FOLLOWING_PLAYER) {
//                releaseAllAstronauts(true);
//                fxAstronautRelease.play();
//            }
            if ((*strandedAstronaut)[i]->FOLLOWING_PLAYER) {
                (*strandedAstronaut)[i]->getPlayerData(pos, v);
                HAVE_ASTRONAUT              = true;
            }
            if (HAVE_ASTRONAUT) {
                if (dist <= pickup_range && !(*strandedAstronaut)[i]->FOLLOWING_ASTRONAUT && !(*strandedAstronaut)[i]->FOLLOWING_PLAYER) {
                    for (int j = 0; j < strandedAstronaut->size(); j++) {
                        if ((*strandedAstronaut)[j]->THE_END) {
                            (*strandedAstronaut)[i]->astronaut = j;
                            (*strandedAstronaut)[i]->FOLLOWING_ASTRONAUT = true;
                            (*strandedAstronaut)[i]->THE_END = true;
                            (*strandedAstronaut)[j]->THE_END = false;
                            j = strandedAstronaut->size();
                        }
                    }
                }
            }
        }
    }
}

void Player::releaseAstronaut() {
    for (int i = 0; i < strandedAstronaut->size(); i++) {
        if ((*strandedAstronaut)[i]->THE_END) {
            if ((*strandedAstronaut)[i]->FOLLOWING_ASTRONAUT) {
                (*strandedAstronaut)[i]->FOLLOWING_ASTRONAUT = false;
                (*strandedAstronaut)[(*strandedAstronaut)[i]->astronaut]->THE_END = true;
            }
//            if ((*strandedAstronaut)[i]->FOLLOWING_PLAYER) {
//                (*strandedAstronaut)[i]->FOLLOWING_PLAYER = false;
//                (*strandedAstronaut)[i]->FOLLOWING_ASTRONAUT = false;
//                (*strandedAstronaut)[i]->THE_END = false;
//                HAVE_ASTRONAUT = false;
//            }
        }
    }
    fxAstronautRelease.play();
    CAN_PICKUP_ASTRONAUTS = false;
}

void Player::releaseAllAstronauts(bool SOUND) {
    for (int i = 0; i < strandedAstronaut->size(); i++) {
        if ((*strandedAstronaut)[i]->FOLLOWING_PLAYER) {
            (*strandedAstronaut)[i]->FOLLOWING_PLAYER = false;
            (*strandedAstronaut)[i]->RELEASED = true;
        }
        if ((*strandedAstronaut)[i]->FOLLOWING_ASTRONAUT) {
            (*strandedAstronaut)[i]->RELEASED = true;
        }
        if ((*strandedAstronaut)[i]->THE_END) {
            (*strandedAstronaut)[i]->THE_END = false;
            (*strandedAstronaut)[i]->RELEASED = true;
        }
    }
    if (SOUND) {
        fxAstronautRelease.play();
    }
    CAN_PICKUP_ASTRONAUTS = false;
    HAVE_ASTRONAUT = false;
}

void Player::detectGravitatorCollisions() {             ///This method only detects if the player is touching a planet
    IN_GRAVITY_WELL = false;
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

        if (!TRAVERSE_MODE) {
            if (dist <= collision_range ) {

                collision               = i;
                collisionData(i);

                if (gravitator_type == "planet") {
                    orientToPlanet(i);
                    gravitatorBounce();
                    v.set(0, 0);
                    f.set(0, 0);
                    USING_GRAVITY       = false;
                    TRAVERSE_MODE       = true;
                }

                HIT_GRAVITATOR          = true;

                if (DEBUG_GUI) {
                    cout << "Collided with a " << gravitator_type << endl;
                }
            }
            if (dist > (planet_r + r) * (planet_r + r)) {

            }
            if (dist < (planet_gravity_range + r) * (planet_gravity_range + r) && USING_GRAVITY) {
                IN_GRAVITY_WELL = true;
                gravity_type = gravitator_type;
                if (SIMPLE_GRAVITY) {
                    gravity               += planet_G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();
                } else {
                    gravity               += planet_G * (m * planet_mass) / (dist) * planet_to_player_normal.normalized();
                }
                if (gravitator_type == "blackhole") {
                    //gravity               += planet_G * (m * planet_mass) / (dist) * planet_to_player_normal.normalized();
                }
            }
        }
        if (TRAVERSE_MODE) {
            collisionData(collision);
            orientToPlanet(collision);
            if (dist <= (planet_r + r) * (planet_r + r)) {

            }
            if (dist > (planet_r + r) * (planet_r + r) + (r * r)) {

            }
        }
    }
}

bool Player::die() {
    if (!GOD_MODE) {
        if (!DEATH_ANIMATION) {
            anim = death;
            fxDeath.play();
        }
        if (death_timer > 0) {
            death_timer -= dt;
            v.set(0, 0);
            gravity.set(0, 0);
            return true;
        }
        if (death_timer <= 0) {
            IS_DEAD = true;
            //setup();
            //releaseAllAstronauts(false);
            //displayMessage(starting_pos, "You died.", (*gui)[0]->dark_grey, (*gui)[0]->red);
            return false;
        }
    } else return false;
}

void Player::drawGUIOverlay(ofVec2f _pos, string text) {
    (*gui).push_back(new GUIOverlay(_pos, text));
}

void Player::displayMessage(ofVec2f _pos, string text) {
    (*gui).push_back(new Message(_pos + ofVec2f(0, -15), text));
}

void Player::displayMessage(ofVec2f _pos, string text, ofColor background_color, ofColor foreground_color) {
    (*gui).push_back(new Message(_pos + ofVec2f(0, -15), text, background_color, foreground_color));
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
    gravitator_type                     = (*gravitator)[collision]->type;

    if (!SIMPLE_GRAVITY) {
        jump_strength_3 = jump_multiplier * planet_m;
    }
    if (DEBUG_GUI) {
        //cout << ofToString(planet_m) << endl;
    }
}

void Player::orientToPlanet(int collision) {
    dir.set(normalized_collision_normal);
    float new_rotation = ofRadToDeg(atan2(normalized_collision_normal.y, normalized_collision_normal.x));
    rotation = ofLerp(rotation, new_rotation, planet_orientation_speed * dt);
}

void Player::traversePlanet(bool move_left) {
    float theta;
    theta = atan2(collision_normal.y / planet_r, collision_normal.x / planet_r);

    if (move_left) {
        theta -= speed_on_planet / planet_r * dt;
        if(anim.index!=0) anim = walking;
        FACING_RIGHT = false;
    } else {
        theta += speed_on_planet / planet_r * dt;
        if(anim.index!=0) anim = walking;
        FACING_RIGHT = true;
    }
    pos.x = (cos(theta) * (planet_r + r)) + planet_pos.x;
    pos.y = (sin(theta) * (planet_r + r)) + planet_pos.y;
    if (!fxWalk.getIsPlaying()) {
        fxWalk.setSpeed(ofRandom(0.8, 1.2));
        fxWalk.play();
    }

}

void Player::rotateDirection(bool rotate_left) {
    if (rotate_left) {
        rotation -= rotation_speed;
    } else {
        rotation += rotation_speed;
    }
    dir.set(cos(ofDegToRad(rotation)), sin(ofDegToRad(rotation)));
    if (!fxJetpackLoop.getIsPlaying()) {
        fxJetpackLoop.play();
    }
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
    if (jumpStrength == 0) {
        anim = charge;
    }
    if (jumpStrength <= jump_strength_3 + 1) {
        jumpStrength += 0.10 * jump_strength_3;
    }
}

void Player::jump() {

    if (anim.frame == 1) {
        jumpStrength = jump_strength_1;
    } else if (anim.frame == 2) {
        jumpStrength = jump_strength_2;
    } else if (anim.frame == 3) {
        jumpStrength = jump_strength_3;
    }

    if (TRAVERSE_MODE) {
        //fxJump[0].play();
        fxJump.setSpeed(ofRandom(0.9, 1.2));
        fxJump.play();
        starting_pos = pos;
        f += jumpStrength;
        LEAVING_PLANET = true;
        anim = lift;
        jump_timer = 0.1;

        if (DEBUG_GUI) {
            cout << "Jumped with " + ofToString(jumpStrength) + "N" << endl;
        }
    }
    jumpStrength = 0;
}

void Player::jetpack(bool JETPACK_FORWARD) {
    if (oxygen - jetpack_o2_use <= 0) {
        CAN_JETPACK = false;
    }
    if (CAN_JETPACK) {
        float angle = dir.angle(v);
        if (abs(angle) > 10) {
            //v.scale(0.5 * v.length());
        }
        if (JETPACK_FORWARD) {
            ofVec2f VEC_MAGNITUDE(jetpack_power, jetpack_power);
            f += VEC_MAGNITUDE;
            oxygen -= jetpack_o2_use;
            CAN_JETPACK = false;
        } else {
            ofVec2f VEC_MAGNITUDE(jetpack_power, jetpack_power);
            f -= VEC_MAGNITUDE;
            oxygen -= jetpack_o2_use;
            CAN_JETPACK = false;
        }
        if (DEBUG_GUI) {
            cout << "impulsed at " + ofToString(f.x, 0) + "N, " + ofToString(f.y, 0) + "N" + nl;
        }
        anim = jetpackFull;
        fxJetpackUse.play();
    } else {
        anim = jetpackEmpty;
        fxJetpackEmpty.play();
    }
}

void Player::keyPressed(ofKeyEventArgs& args) {
    /// TODO (Aaron#9#): Determine why player key listener doesn't apply input (it registers key presses)
    switch (args.key) {
    case 'g':
        break;
    }

    if (!HIT_GRAVITATOR) {
        switch (args.key) {
        case OF_KEY_UP:
            chargeJump();
            break;
        case OF_KEY_LEFT:

            break;
        case OF_KEY_RIGHT:

            break;
        case OF_KEY_DOWN:

            cout << "impulsed at " + nl;

            break;
        case 32:
            break;
        }
    }
}

void Player::keyReleased(ofKeyEventArgs& args) {

}
