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
    f.set(0,0);
    v.set(0,0);
    dir.set(-1, 0);
    pos.set(starting_pos);

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
    jump_strength_1         = 250000.0;
    jump_strength_2         = 500000.0;
    jump_strength_3         = 1000000.0;
    restitution             = 0.50;         /// Used to calculate the amount of momentum conserved when bouncing off a planet
    off_screen_limit        = 0;           /// If this is too large & camera moves by whole screens, camera will freak out
    rotation_speed          = 4.0;          /// This is the speed of your rotation in space
    speed_on_planet         = 150.0;
    jetpack_power           = 1000000.0;
    jump_multiplier         = 30.0;
    jetpack_o2_use          = (max_oxygen / 50) - 1;
    astronaut_pickup_range  = 20;
    astronaut_drop_range    = 120;
    jetpack_count           = 99999;
    max_jetpack_count       = jetpack_count;
    planet_orientation_speed= 50.0;
    oxygen_depletion_speed  = 7.0;
    camera_move_delay       = 0.25;
    death_timer             = 0.5;
    flame_rotation          = 0;
    v_limit                 = 1000.0;

    HIT_GRAVITATOR          = false;
    TRAVERSE_MODE           = false;
    USING_GRAVITY           = true;
    ORIENT_TO_PLANET        = true;
    CAN_JETPACK             = true;
    OFF_SCREEN_CHECK        = true;
    SIMPLE_GRAVITY          = true;
    GOD_MODE                = false;
    LEAVING_PLANET          = false;
    DEATH_ANIMATION         = false;
    JETPACK_EMPTY           = false;
    FACING_RIGHT            = true;
    ROTATE_LEFT             = false;
    ROTATE_RIGHT            = false;

    p1Renderer = new ofxSpriteSheetRenderer(1, 10000, 0, 32);               /// declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 64
	p1Renderer->loadTexture("ART/playerSheet2.png", 384, GL_NEAREST);           /// load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    gravitator_type         = "null";
    anim = idle;
    ofEnableAlphaBlending();
}

void Player::loadSound() {
    fxDeath.loadSound("AUDIO/ksc_AUDIO_astronaut_death_002.wav");
    fxJetpackEmpty.loadSound("AUDIO/ksc_AUDIO_player_jetout_001.wav");
    fxJetpackUse.loadSound("AUDIO/ksc_AUDIO_player_usejet_001.wav");
    fxAstronautCollect.loadSound("AUDIO/ksc_AUDIO_astro_pickup_001.wav");
    fxAstronautRelease.loadSound("AUDIO/ksc_AUDIO_astronaut_death_001.wav");

    fxDeath.setVolume(0.75);
    fxJetpackUse.setVolume(.75);
    fxAstronautCollect.setVolume(.5);
    fxAstronautRelease.setVolume(.5);
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
//    if (!TRAVERSE_MODE) {
        a           = (f / m) * dt;
        v          += dir * a * dt;
        v          += gravity * dt;
        v          *= damp;
        if (v.length() > v_limit) {
            v.set(v.getScaled(v_limit));
        }
        pos        += v * dt;
/*
    }
    if (TRAVERSE_MODE) {
        a           = (f / m) * dt;
        v          += dir * a * dt;
        pos        += v * dt;
    }
*/
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
    int x = 1000 + camera_pos.x;
    int y = 600 + camera_pos.y;
    string gui = "";
    gui += "O2: " + ofToString(oxygen, 2) + nl;
    ofSetColor(0, 50, 255);
    //ofDrawBitmapString(gui, x + camera_pos.x, y + camera_pos.y);
    ofPushMatrix();
    float o2_percent = oxygen / max_oxygen;
    ofSetColor(255 - (255 * o2_percent), 0, 255 * o2_percent);
    ofRect(ofPoint(x, y), 20, -oxygen / 2);
    ofPopMatrix();
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
    //if (CAN_LAND_ON_PLANET) {
    //    info_b.append("CAN LAND ON PLANET, BRO \n");
    //}
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
        jetpack_count = max_jetpack_count;
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
    }
    if (ROTATE_LEFT && TRAVERSE_MODE) {
        traversePlanet(true);
    }
    if (ROTATE_RIGHT && TRAVERSE_MODE) {
        traversePlanet(false);
    }
    if (ROTATE_LEFT && !TRAVERSE_MODE) {
        rotateDirection(true);
    }
    if (ROTATE_RIGHT && !TRAVERSE_MODE) {
        rotateDirection(false);
    }

    ///---------------------
    /// GRAVITATORS
    ///---------------------
    if (TRAVERSE_MODE) {
        if (gravitator_type != "blackhole") {
            oxygen          = max_oxygen;
            jetpack_count   = max_jetpack_count;
        }
    }
    if (!TRAVERSE_MODE) {
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
        //orientToPlanet(collision);
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
        if (pos.x > camera_target.x + screen_width - off_screen_limit) {
            camera_move_direction = "right";
            camera_timer = camera_move_delay;
            return true;
        }
        if (pos.x < camera_target.x + off_screen_limit) {
            camera_move_direction = "left";
            camera_timer = camera_move_delay;
            return true;
        }
        if (pos.y > camera_target.y + screen_height - off_screen_limit) {
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
        float dist                  = pos.distance((*strandedAstronaut)[i]->pos);
        float astronaut_r           = (*strandedAstronaut)[i]->r;

        if (dist <= r + astronaut_r + astronaut_pickup_range && (*strandedAstronaut)[i]->FOLLOWING_PLAYER == false ) {
            (*strandedAstronaut)[i]->FOLLOWING_PLAYER = true;
            fxAstronautCollect.play();
            if (DEBUG_GUI) {
                cout << "I'm Astronaut #" + ofToString(i) + " and I'm following you!" << endl;
            }
        }
        if (dist > r + astronaut_r + astronaut_drop_range && (*strandedAstronaut)[i]->FOLLOWING_PLAYER == true) {
            (*strandedAstronaut)[i]->FOLLOWING_PLAYER = false;
            fxAstronautRelease.play();
        }
        if ((*strandedAstronaut)[i]->FOLLOWING_PLAYER == true) {
            (*strandedAstronaut)[i]->getPlayerData(pos);
        }
    }
}

void Player::releaseAstronaut(int i) {
    (*strandedAstronaut)[i]->FOLLOWING_PLAYER = false;
    fxAstronautRelease.play();
}

void Player::releaseAllAstronauts(bool SOUND) {
    for (int i = 0; i < strandedAstronaut->size(); i++) {
        (*strandedAstronaut)[i]->FOLLOWING_PLAYER = false;
    }
    if (SOUND) {
        fxAstronautRelease.play();
    }
}

void Player::detectGravitatorCollisions() {             ///This method only detects if the player is touching a planet
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

        if (!TRAVERSE_MODE) {
            if (dist <= (planet_r + r) * (planet_r + r)) {

                collision               = i;
                collisionData(i);
                orientToPlanet(i);

                if (gravitator_type == "planet") {
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
                if (SIMPLE_GRAVITY) {
                    gravity               += planet_G * planet_to_player_normal.normalized() / planet_to_player_normal.length() * planet_to_player_normal.length();
                } else {
                    gravity               += planet_G * (m * planet_mass) / (dist) * planet_to_player_normal.normalized();
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
            setup();
            releaseAllAstronauts(false);
            displayMessage(starting_pos, "You died.", (*gui)[0]->dark_grey, (*gui)[0]->red);
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
    if (jetpack_count > 0 && CAN_JETPACK) {
        float angle = dir.angle(v);
        if (abs(angle) > 10) {
            v.set(0, 0);
        }
        if (JETPACK_FORWARD) {
            ofVec2f VEC_MAGNITUDE(jetpack_power, jetpack_power);
            f += VEC_MAGNITUDE;
            oxygen -= jetpack_o2_use;
            jetpack_count--;
            CAN_JETPACK = false;
        } else {
            ofVec2f VEC_MAGNITUDE(jetpack_power, jetpack_power);
            f -= VEC_MAGNITUDE;
            oxygen -= jetpack_o2_use;
            jetpack_count--;
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
