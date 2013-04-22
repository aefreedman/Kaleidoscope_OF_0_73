#include "GameScreen.h"

#include <fstream>

#define nl '\n'
#define screen_width 1280
#define screen_height 720
#define dt 1.0/60.0
#define spacer "  >>  "
#define bar "  ||  "
#define gap "   "

//--------------------------------------------------------------
GameScreen::GameScreen() : Screen() {

}

GameScreen::~GameScreen() {}

void GameScreen::setup() {
    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    camera_pos.set(0, 0, 0);
    camera_target.set(0, 0, 0);
    CAN_EDIT_LEVEL                  = false;
    CAMERA_SCALING                  = false;
    WON_LEVEL                       = false;
    MAP_VIEW                        = false;
    default_view_scale              = 1;
    view_scale                      = 1;
    view_scale_target               = 1;
    background.loadImage("ART/bg.png");
    fadeIn                          = GUIFadeIn(camera_pos);

    ///------------------------------
    /// YOU CAN CHANGE THESE
    ///------------------------------

    player_start_pos.set(screen_width / 2, screen_height / 2);
    planet_base_m                   = 1000;
    planet_mass_multiplier          = 250;
    camera_lerp_speed               = 4; /// NOTE (Aaron#9#): This should change depending on player velocity
    view_lerp_speed                 = 4;
    map_view_scale_target           = .25;
    levelID                         = 0;

    //LOAD_WITH_SOUND                 = true;
    CONTINUOUS_CAMERA               = true;
    MOVE_MESSAGES                   = false;
    ENABLE_EDITOR                   = false;

    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------
    player                          = Player(player_start_pos, &gravitator, &strandedAstronaut, &gui);
    clickState                      = "play mode";
    levelState                      = "Working from scratch.";
    new_gravitator_type             = "";
    if (LOAD_WITH_SOUND) {
        loadSound();
        player.loadSound();
    }
    importLevel(levelID);

    planetRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 128); //declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
    planetRenderer->loadTexture("ART/planets.png", 256, GL_NEAREST); // load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    nautRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 64);             /// declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
    nautRenderer->loadTexture("ART/nauts.png", 512, GL_NEAREST);                /// load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    ofEnableAlphaBlending(); // turn on alpha blending. important!

    //HUD

    O2frame.loadImage("ART/O2_frame.png");
    O2bar.loadImage("ART/O2_bar.png");
    map.loadImage("ART/map.png");

}

void GameScreen::loadSound() {
    jupiterSound.loadSound("AUDIO/ksc_AUDIO_background_music_001.mp3");
    jupiterSound.setLoop(true);
    jupiterSound.setVolume(0.3);
    jupiterSound.play();
    backgroundSound.loadSound("AUDIO/background.wav");
    backgroundSound.setLoop(true);
    backgroundSound.setVolume(0.25);
    backgroundSound.play();

}

//--------------------------------------------------------------
void GameScreen::update() {
    if (clickState != "play mode") {
        PAUSE = true;
    } else if (!MAP_VIEW) {
        PAUSE = false;
    }
    if (!PAUSE) {
        player.update();
        fadeIn.update();
        if (player.IS_DEAD) {
            reset();
        }
        for (int i = 0; i < gravitator.size(); i++) {
            gravitator[i]->update();
        }
        for (int i = 0; i < strandedAstronaut.size(); i++) {
            strandedAstronaut[i]->id = i;
            strandedAstronaut[i]->update();
            if (strandedAstronaut[i]->IS_DEAD) {
                for (int j = 0; j < strandedAstronaut.size(); j++) {
                    if (strandedAstronaut[j]->astronaut == i) {
                        strandedAstronaut[j]->FOLLOWING_ASTRONAUT = false;
                        strandedAstronaut[j]->THE_END = false;
                    }
                }
                delete strandedAstronaut[i];
                strandedAstronaut.erase(strandedAstronaut.begin()+i);
            }
        }
        for (int i = 0; i < gui.size(); i++) {
            gui[i]->update();
            if (!gui[i]->ACTIVE) {
                //delete gui[i];
                //gui.erase(gui.begin()+i);
            }
            if ((gui[i]->pos.x > ofGetWidth() + camera_target.x - 50 || gui[i]->pos.y > ofGetHeight() + camera_target.y + 30 || gui[i]->pos.x < camera_target.x - 50 || gui[i]->pos.y < camera_target.y + 30) && camera_pos.squareDistance(camera_target) < 10) {
                //gui[i]->pos.interpolate(gui[i]->pos.getMiddle(player.pos), 1);
                gui[i]->pos.interpolate(player.pos, 10 * dt);
            }
            if (MOVE_MESSAGES) {

/*                ofVec3f t;
                ofVec3f u;
                ofVec3f r;
                ofVec3f p;
                p.set(player.pos.x, player.pos.y, 0);
                r.set(gui[i]->pos.x, gui[i]->pos.y, 0);*/

                if (gui[i]->pos.x > ofGetWidth() + camera_pos.x) { ///Off right

                    ofVec3f q;
                    ofVec3f s;
                    q.set(camera_pos.x + ofGetWidth(), camera_pos.y + ofGetHeight(), 0);
                    s.set(camera_pos.x + ofGetWidth(), camera_pos.y, 0);
/*
                    t = s.getCrossed(q - p) / s.getCrossed(r);
                    u = r.getCrossed(q - p) / s.getCrossed(r);
                    gui[i]->pos.set(p + (t * r));
                    gui[i]->pos.middle(p);
                    //gui[i]->pos.x = camera_pos.x + (r.x * t.z);
                    //gui[i]->pos.y = camera_pos.y + (r.y * t.z);*/

                } else if (gui[i]->pos.y > ofGetHeight() + camera_pos.y) { /// Below

/*                    ofVec3f q;
                    ofVec3f s;
                    q.set(camera_pos.x + ofGetWidth(), camera_pos.y + ofGetHeight(), 0);
                    s.set(camera_pos.x, camera_pos.y + ofGetHeight(), 0);

                    t = s.getCrossed(q - p) / s.getCrossed(r);
                    u = r.getCrossed(q - p) / s.getCrossed(r);
                    gui[i]->pos.set(p + (t * r));
                    gui[i]->pos.middle(p);
*/
                } else if (gui[i]->pos.x < camera_pos.x) { /// Off left

/*                    ofVec3f q;
                    ofVec3f s;
                    q.set(camera_pos.x, camera_pos.y, 0);
                    s.set(camera_pos.x, camera_pos.y + ofGetHeight(), 0);

                    t = s.getCrossed(q - p) / s.getCrossed(r);
                    u = r.getCrossed(q - p) / s.getCrossed(r);
                    gui[i]->pos.set(p + (t * r));
                    gui[i]->pos.middle(p);
                    //gui[i]->pos.x = p.x + (t.z);
                    //gui[i]->pos.y = p.y + (t.z);
*/
                } else if (gui[i]->pos.y < camera_pos.y) { /// Above

/*                    ofVec3f q;
                    ofVec3f s;
                    q.set(camera_pos.x, camera_pos.y, 0);
                    s.set(camera_pos.x + ofGetWidth(), camera_pos.y, 0);

                    t = s.getCrossed(q - p) / s.getCrossed(r);
                    u = r.getCrossed(q - p) / s.getCrossed(r);
                    gui[i]->pos.set(p + (t * r));
                    gui[i]->pos.middle(p);
*/
                }
            }
        }
        if (LEVEL_HAS_ASTRONAUTS && strandedAstronaut.size() == 0) {
            WON_LEVEL = true;
        }
        if (WON_LEVEL) {
            levelID++;
            importLevel(levelID);
        }
    }

    /// TODO (Aaron#1#): Map view needs to account for camera position when scaling

    if (CONTINUOUS_CAMERA && clickState == "play mode" && !PAUSE && !MAP_VIEW) {
        moveCamera();
    }
    if (!CONTINUOUS_CAMERA && player.OFF_SCREEN == true && clickState == "play mode") {
        moveCamera(player.camera_move_direction);
        player.OFF_SCREEN = false;
    }
    player.camera_pos = camera_pos;
    player.camera_target = camera_target;

    view_scale = ofLerp(view_scale, view_scale_target, view_lerp_speed * dt);
    if (view_scale >= view_scale_target * 0.95 && view_scale <= view_scale_target * 1.05) {
        CAMERA_SCALING = false;
    }   else {
        CAMERA_SCALING = true;
    }
    camera_pos.interpolate(camera_target, camera_lerp_speed * dt);
    fadeIn.pos.interpolate(camera_target, camera_lerp_speed * dt);

    planetRenderer->clear(); // clear the sheet
    for(int i = 0; i < gravitator.size(); i++) {
        float scaleFactor;
        if (gravitator[i]->type == "comet") {
            scaleFactor = 2;
        } else if (gravitator[i]-> type == "planet") {
            scaleFactor = 4.0*gravitator[i]->r/120.0;
        } else if (gravitator[i]->type == "sun") {
            scaleFactor = 2 * gravitator[i]->r/128.0;
        } else if (gravitator[i]->type == "blackhole") {
            scaleFactor = 0;
        }
        planetRenderer->addCenteredTile(&gravitator[i]->anim,gravitator[i]->pos.x,gravitator[i]->pos.y,-1,F_NONE,scaleFactor,255,255,255,255);
    }
    planetRenderer->update(ofGetElapsedTimeMillis());
    nautRenderer->clear(); // clear the sheet
    for (int i=0; i<strandedAstronaut.size(); i++) {
        float scaleFactor = 1;
        nautRenderer->addCenteredTile(&strandedAstronaut[i]->anim,strandedAstronaut[i]->pos.x,strandedAstronaut[i]->pos.y,-1,F_NONE,scaleFactor,255,255,255,255);
    }
    nautRenderer->update(ofGetElapsedTimeMillis());




}

void GameScreen::moveCamera(string direction) {
    ofVec2f target;
    if (!CAMERA_SCALING) {
        if (direction == "up") {
            target.set(0, -screen_height * view_scale);
        } else if (direction == "down") {
            target.set(0, screen_height * view_scale);
        } else if (direction == "left") {
            target.set(-screen_width * view_scale, 0);
        } else if (direction == "right") {
            target.set(screen_width * view_scale, 0);
        }
    }

    target += camera_target;
    camera_target.x = target.x;
    camera_target.y = target.y;
    camera_target.z = 0;


}

void GameScreen::moveCamera() {
    camera_target.x = player.pos.x - screen_width/2;
    camera_target.y = player.pos.y - screen_height/2;
}

//--------------------------------------------------------------
void GameScreen::draw() {
    ///Draw events that go behind the camera, but are not affected by zoom go below
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(-camera_pos);
    background.draw(camera_pos);
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(camera_target);
    //ofRotate(50, 0, 0, 1);
    ofScale(view_scale, view_scale, 1);
    ofSetColor(255,255,255,50);

    ofPopMatrix();


    ///Draw events that should be subject to camera go below
    ofPushMatrix();
    ofTranslate(-camera_pos);
    //ofRotate(50, 0, 0, 1);
    ofScale(view_scale, view_scale, 1);
    ofSetColor(255,255,255);

    if (clickState != "play mode") {   /// FIXME (Aaron#1#): BROKEN
        for (int i = 0; i < 4; i++) {
            ofPolyline line;
            line.addVertex(1280 * i, 0);
            line.addVertex(1280 * i, 8000);
            line.draw();
        }
        for (int i = 0; i< 4; i++) {
            ofPolyline line;
            line.addVertex(0, 720 * i);
            line.addVertex(8000, 720 * i);
            line.draw();
        }
    }
    for (int i = 0; i < gravitator.size(); i++) {
        gravitator[i]->draw();
    }

    planetRenderer -> draw();
    nautRenderer -> draw();

    for (int i = 0; i < gui.size(); i++) {
        gui[i]->draw();
    }
    for (int i = 0; i < strandedAstronaut.size(); i++) {
        strandedAstronaut[i]->draw();
    }
    player.draw();

    if (!MAP_VIEW) {
        ofSetColor(255, 255, 255);
        for (int i = 0; i < totalCrew; i++) {
            if (i < strandedAstronaut.size()){
                ofSetColor(255, 255, 255);
                ofRect(36+(10*i) + camera_pos.x, camera_pos.y + ofGetHeight() - map.height + 46, 5,5);
            } else {
                ofSetColor(223, 42, 99);
                ofRect(36+(10*i) + camera_pos.x, camera_pos.y + ofGetHeight() - map.height + 46, 5,5);
            }
        }
        int x = ofGetWidth() + camera_pos.x - 53;
        int y = ofGetHeight() + camera_pos.y - 26;
        float o2_percent = player.oxygen / player.max_oxygen;
        ofSetColor(88 - (88 * o2_percent), 211, 222 * o2_percent);
        ofRect(ofPoint(x, y), 20, -136 * o2_percent);

        int percentOut = 400 * (1 -(player.oxygen/player.max_oxygen));

        ofSetColor(255,255,255,255);
        //O2bar.draw(camera_pos.x + ofGetWidth()-O2bar.width - 34,camera_pos.y + ofGetHeight()-O2bar.height - 24);
        O2frame.draw(camera_pos.x + ofGetWidth()-O2frame.width - 20,camera_pos.y + ofGetHeight()-O2frame.height - 20);

        map.draw(camera_pos.x,camera_pos.y + ofGetHeight() - map.height);
    }
    fadeIn.draw();
    ofPopMatrix();

    ///Draw events that go on top of camera but are not subject to camera go below

    ///LEVEL EDITOR---------------------------------------------
    int text_gap = 15;
    if (clickState == "setting size") {
        ofSetColor(0,255,0);
        ofNoFill();
        ofPushMatrix();
        ofCircle(NEW_PLANET_POS, ofDist(mouseX, mouseY, NEW_PLANET_POS.x, NEW_PLANET_POS.y));
        ofPopMatrix();
    }
    if (clickState == "setting grav") {
        ofSetColor(0,255,0);
        ofNoFill();
        ofCircle(NEW_PLANET_POS,ofDist(mouseX,mouseY,NEW_PLANET_POS.x,NEW_PLANET_POS.y));
        ofSetColor(230,230,255);
        ofNoFill();
        ofPushMatrix();
        ofCircle(NEW_PLANET_POS,NEW_PLANET_R);
        ofPopMatrix();
    }
    if (clickState == "sizing comet") {
        ofPushMatrix();
        ofSetColor(255, 100, 100);
        ofNoFill;
        ofCircle(NEW_COMET_POS, ofDist(mouseX, mouseY, NEW_COMET_POS.x, NEW_COMET_POS.y));
        ofPopMatrix();
    }
    if (clickState == "placing comet") {
        ofPushMatrix();
        ofSetColor(255, 100, 100);
        ofNoFill();
        ofCircle(mouseX, mouseY, 10);
        ofPopMatrix();
    }



    ///TOP TEXT DISPLAY-----------------------------------------

    string top_text = "";
    top_text.append("level " + ofToString(levelID));
    top_text.append(spacer);
    top_text.append(clickState);
    top_text.append(gap);
    if (clickState == "play mode") {
        top_text.append("[F1] to edit level");
        top_text.append(bar);
        top_text.append("[P] to place player");
        top_text.append(gap);
        top_text.append(ofToString(camera_pos, 2));
        top_text.append(gap);
        top_text.append(ofToString(camera_target, 2));
        top_text.append(gap);
        top_text.append(ofToString(camera_target_save, 2));
    } else if (clickState == "edit mode") {
        top_text.append(levelState);
        top_text.append(gap);
        top_text.append(gap);
        top_text.append("[F2] (previous level) || [F3] (next level) || [F5] save level");
    }
    if (PAUSE) {
        top_text.append("\n");
        top_text.append("\n");
        top_text.append("PAUSED");
    }

    if (clickState != "play mode") {
        ofPushMatrix();
        ofSetColor(0, 255, 0);
        ofDrawBitmapString(top_text, 1, 10);
        ofPopMatrix();
    }

    ///FLOATING MOUSE TEXT ----------------------------------
    if (clickState != "play mode") {
        int draw_x = mouseX + 20;
        int draw_y1 = mouseY + 20;
        int draw_y2 = draw_y1 + 15;

        if (clickState != "edit mode") {
            string mouse_text = "";
            mouse_text.append("placing: ");
            mouse_text.append(new_gravitator_type);
            if (clickState == "placing player") {
                mouse_text.append("player");
            }
            if (clickState == "placing astronaut") {
                mouse_text.append("astronaut");
            }
            if (clickState == "placing comet") {
                mouse_text.append("comet");
            }
            if (clickState == "placing path") {
                mouse_text.append("comet path");
            }
            ofDrawBitmapString(mouse_text, draw_x, draw_y1);
        }

        string placement_text = "";
        if (clickState == "placing gravitators") {
            placement_text.append("click & drag to make gravitator \n");
            placement_text.append("press [UP] to cycle placement type");
        } else if (clickState == "setting size") {
            placement_text = "release to set size.";
        } else if (clickState == "setting grav") {
            placement_text = "click to set gravity range.";
        } else if (clickState == "placing player") {
            placement_text = "click to set player location";
        } else if (clickState == "placing path") {
            placement_text = "[c] to stop placing path";
        } else placement_text = "";
        ofDrawBitmapString(placement_text, draw_x, draw_y2);

        if (clickState == "edit mode") {
            int x = 50;
            int y = 100;
            string info = "";
            info.append("[p] to place gravitators \n");
            info.append("[C] to clear gravitators \n\n");
            info.append("[c] to place comet \n");
            info.append("[a] to place astronaut \n");
            info.append("[A] to clear astronauts \n");
            ofDrawBitmapString(info, draw_x, draw_y1);
        }
    }
}

void GameScreen::reset() {
    importLevel(levelID);
    player.setup();
    //fadeIn.pos.set(ofVec2f(camera_target.x, camera_target.y));
    fadeIn.setup();
}

void GameScreen::addGravitator() {
    if (new_gravitator_type == "planet") {
        gravitator.push_back(new Planet((NEW_PLANET_POS + camera_pos) / view_scale, NEW_PLANET_R / view_scale, NEW_PLANET_M, NEW_PLANET_GR / view_scale));
    }
    if (new_gravitator_type == "sun") {
        gravitator.push_back(new Sun((NEW_PLANET_POS + camera_pos) / view_scale, NEW_PLANET_R / view_scale, NEW_PLANET_M, NEW_PLANET_GR / view_scale));
    }
    if (new_gravitator_type == "black hole") {
        gravitator.push_back(new BlackHole((NEW_PLANET_POS + camera_pos) / view_scale, NEW_PLANET_R / view_scale, NEW_PLANET_M, NEW_PLANET_GR / view_scale));
    }
    new_gravitator_type = "";
}

void GameScreen::addStrandedAstronaut(ofVec2f _pos) {
    strandedAstronaut.push_back(new StrandedAstronaut((_pos + camera_pos) / view_scale, &gravitator, &strandedAstronaut, &gui));
}

//--------------------------------------------------------------
void GameScreen::keyPressed(int key) {

    //justPressed.push_back(key);

    switch (key) {
    case 'i':
        if (iddqd == 0) {
            iddqd = 1;
        }
        break;
    case 'd':
        if (MAP_VIEW || clickState != "play mode") {
            moveCamera("right");
        }
        if (iddqd == 1 || iddqd == 2) {
            iddqd++;
        }
        if (iddqd == 4) {
            player.GOD_MODE = !player.GOD_MODE;
            iddqd = 0;
        }
        break;
    case 'q':
        if (iddqd == 3) {
            iddqd = 4;
        }
        break;
    case OF_KEY_F1:
        if (ENABLE_EDITOR) {
            CAN_EDIT_LEVEL = !CAN_EDIT_LEVEL;
            if (clickState == "play mode") {
                clickState = "edit mode";
            } else {
                clickState = "play mode";
            }
        }
        break;
    case 'p':
        if (CAN_EDIT_LEVEL && clickState == "edit mode") {
            clickState = "placing gravitators";
            new_gravitator_type = "planet";
        }
        break;
    case 'a':
        if (CAN_EDIT_LEVEL && clickState == "edit mode") {
            clickState = "placing astronaut";
        } else if (MAP_VIEW || clickState != "play mode") {
            moveCamera("left");
        }
        break;
    case 'A':
        if (CAN_EDIT_LEVEL) {
            strandedAstronaut.clear();
        }
        break;
    case 's':
        if (MAP_VIEW || clickState != "play mode") {
            moveCamera("down");
        }
        break;
    case 'P':
        if (clickState != "play mode") {
            clickState = "placing player";
            player.setup();
        }
        break;
    case OF_KEY_F5:
        if (clickState != "play mode") {
            exportLevel();
        }
        break;
    case OF_KEY_F2:
        if (clickState != "play mode") {
            if (levelID > 0) {
                levelID--;
                importLevel(levelID);
            }
        }
        break;
    case OF_KEY_F3:
        if (clickState != "play mode") {
            levelID++;
            if (levelState != "That level doesn't exist.") {
                importLevel(levelID);
            }
        }
        break;
    case 'c':
        if (CAN_EDIT_LEVEL) {
            if (clickState == "placing path") {
                clickState = "edit mode";
            } else {
                clickState = "placing comet";
            }
        }
        break;
    case 'C':
        if (CAN_EDIT_LEVEL) {
            gravitator.clear();
        }
        break;
    case 'g':
        player.USING_GRAVITY = !player.USING_GRAVITY;
        break;
    case 'G':
        player.SIMPLE_GRAVITY = !player.SIMPLE_GRAVITY;
        break;
    case OF_KEY_UP:
        if (clickState == "placing gravitators") {
            if (new_gravitator_type == "") {
                new_gravitator_type = "planet";
                break;
            }
            if (new_gravitator_type == "planet") {
                new_gravitator_type = "sun";
                break;
            }
            if (new_gravitator_type == "sun") {
                new_gravitator_type = "black hole";
                break;
            }
            if (new_gravitator_type == "black hole") {
                new_gravitator_type = "planet";
                break;
            }
        }
        if (player.CAN_JETPACK && !player.TRAVERSE_MODE && !player.DEATH_ANIMATION) {
            player.jetpack(true);
            break;
        } else if (player.TRAVERSE_MODE) {
            player.chargeJump();
            break;
        }
    case OF_KEY_DOWN:
        break;
    case OF_KEY_LEFT:
        player.ROTATE_LEFT = true;
        if (!player.TRAVERSE_MODE) {
            player.fxRotate.play();
        }
        break;
    case OF_KEY_RIGHT:
        player.ROTATE_RIGHT = true;
        if (!player.TRAVERSE_MODE) {
            player.fxRotate.play();
        }
        break;
    case 'w':
        if (MAP_VIEW || clickState != "play mode") {
            moveCamera("up");
        }
        break;
    case 'x':
        player.releaseAllAstronauts(true);
        //player.releaseAstronaut();
        break;
    case 32:
        if (player.CAN_JETPACK && !player.TRAVERSE_MODE && !player.DEATH_ANIMATION) {
            player.jetpack(true);
            break;
        } else if (player.TRAVERSE_MODE) {
            player.chargeJump();
            break;
        }
        break;
    case '=':
        player.damp += 0.01;
        break;
    case '-':
        player.damp -= 0.01;
        break;
    case 'm':
        if (!MAP_VIEW) {
            //camera_target_save = camera_target;
            view_scale_target = map_view_scale_target;
        } else if (MAP_VIEW) {
            //camera_target = camera_target_save;
            view_scale_target = default_view_scale;
            camera_target.set(0, 0, 0);
        }
        MAP_VIEW = !MAP_VIEW;
        PAUSE = !PAUSE;
        break;
    case 'R':
        reset();
        break;
    }
}

//--------------------------------------------------------------
void GameScreen::keyReleased(int key) {

    /*for (int i = 0; i < justPressed.size(); i++){
        if (justPressed[i] == key){
            justPressed[i]erase();
        }
    }*/

    switch (key) {
    case 'a':
        break;
    case 'd':
        break;
    case OF_KEY_UP:
        if (player.TRAVERSE_MODE) {
            player.jump();
            if (!ENABLE_EDITOR) {
                exportLevel();
            }
            break;
        } else {
            player.CAN_JETPACK = true;
            break;
        }
    case 32:
        if (player.TRAVERSE_MODE) {
            player.jump();
            break;
        } else {
            player.CAN_JETPACK = true;
            break;
        }
        break;
    case OF_KEY_LEFT:
        player.ROTATE_LEFT = false;
        player.anim = idle;
        break;
    case OF_KEY_RIGHT:
        player.ROTATE_RIGHT = false;
        player.anim = idle;
        break;
    }

}

//--------------------------------------------------------------
void GameScreen::mouseMoved(int x, int y ) {
    if (clickState == "placing player") {
        player.pos.set((x + camera_pos.x) / view_scale, (y + camera_pos.y) / view_scale);
    }

}

//--------------------------------------------------------------
void GameScreen::mouseDragged(int x, int y, int button) {
    if (clickState == "edit mode") {
        ofVec2f mouse_pos;
        mouse_pos.set(x, y);
        mouse_pos += camera_pos;
        for (int i = 0; i < gravitator.size(); i++) {
            ofVec2f g_pos;
            g_pos.set(gravitator[i]->pos / view_scale);
            /// NOTE (Aaron#1#): This needs to be updated to account for view_scale
            if (g_pos.x > camera_pos.x && g_pos.x < camera_pos.x + screen_width && g_pos.y > camera_pos.y && g_pos.y < camera_pos.y + screen_height) {
                float dist = mouse_pos.squareDistance(gravitator[i]->pos);
                if (dist <= gravitator[i]->r * gravitator[i]->r && button == 0 && clickState == "edit mode") {
                    gravitator[i]->pos = mouse_pos;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void GameScreen::mousePressed(int x, int y, int button) {
    if (clickState == "edit mode" && button == 2) {

    }

    if (clickState == "placing gravitators") {
        NEW_PLANET_POS.set(0,0);
        NEW_PLANET_R = 0;
        NEW_PLANET_GR = 0;
        NEW_PLANET_M = 0;
        NEW_PLANET_POS.set(x, y);
        clickState = "setting size";
    }
    if (clickState == "setting grav") {
        if (NEW_PLANET_R < 1) {
            clickState = "edit mode";
            return;
        }
        NEW_PLANET_GR = ofDist(x, y, NEW_PLANET_POS.x, NEW_PLANET_POS.y);
        NEW_PLANET_M = (planet_base_m * NEW_PLANET_R) + (NEW_PLANET_GR * planet_mass_multiplier / NEW_PLANET_R);
        addGravitator();
        clickState = "edit mode";
    }
    if (clickState == "play mode") {

    }
    if (clickState == "placing comet") {
        NEW_COMET_POS.set (x, y);
        clickState = "sizing comet";
    }
    if (clickState == "sizing comet") {
        NEW_COMET_R = ofDist(x, y, NEW_COMET_POS.x, NEW_COMET_POS.y);
        vector <ofVec2f> temp;
        ofVec2f start;
        start.set((NEW_COMET_POS + camera_pos) / view_scale);
        temp.push_back(start);
        gravitator.push_back(new Comet((NEW_COMET_POS + camera_pos) / view_scale, NEW_COMET_R, temp));
        clickState = "placing path";
    }
    if (clickState == "placing path") {
        gravitator[gravitator.size()-1]->pathPoints.push_back(ofVec2f((x + camera_pos.x) / view_scale, (y + camera_pos.y) / view_scale));
    }
    if (clickState == "placing player") {
        player.pos.set(ofVec2f((mouseX + camera_pos.x) / view_scale, (mouseY + camera_pos.y) / view_scale));
        player.starting_pos.set(player.pos);
        clickState = "play mode";
    }
    if (clickState == "placing astronaut") {
        addStrandedAstronaut(ofVec2f(mouseX, mouseY));
        clickState = "edit mode";
    }
}

//--------------------------------------------------------------
void GameScreen::mouseReleased(int x, int y, int button) {
    if (clickState == "setting size") {
        NEW_PLANET_R = ofDist(x, y, NEW_PLANET_POS.x, NEW_PLANET_POS.y);
        clickState = "setting grav";
    }

}

//--------------------------------------------------------------
void GameScreen::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void GameScreen::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void GameScreen::dragEvent(ofDragInfo dragInfo) {

}

void GameScreen::exportLevel() {
    while (true) {
        string levelName;
        if (ENABLE_EDITOR) {
            levelName = "level_" + ofToString(levelID);
        }
        if (!ENABLE_EDITOR) {
            levelName = "level_" + ofToString(levelID) + ".sav";
        }
        std::ifstream input(levelName.c_str());
 //       if  (input.good()) {
            std::ofstream output(levelName.c_str());
            output << gravitator.size() + strandedAstronaut.size() << std::endl;
            output << player.starting_pos.x << ' ' << player.starting_pos.y << std::endl;
            for (int i = 0; i < gravitator.size(); i++) {
                output << gravitator[i]->pos.x << ' '
                << gravitator[i]->pos.y << ' '
                << gravitator[i]->r << ' '
                << gravitator[i]->m << ' '
                << gravitator[i]->gR << ' '
                << gravitator[i]->type << ' '
                << gravitator[i]->pathPoints.size() << ' ';
                for (int j = 0; j < gravitator[i]->pathPoints.size(); j++) {
                    output << gravitator[i]->pathPoints[j].x << ' '
                    << gravitator[i]->pathPoints[j].y << ' ';
                }
                output << std::endl;
            }
            for (int i = 0; i < strandedAstronaut.size(); i++) {
                output << strandedAstronaut[i]->pos.x << ' '
                << strandedAstronaut[i]->pos.y << ' '
                << 0 << ' '
                << 0 << ' '
                << 0 << ' '
                << strandedAstronaut[i]->type << ' '
                << 0 << ' '
                << std::endl;
            }
            levelState = ofToString(levelName) + " saved";
            break;
  //      }
    }
}

void GameScreen::importLevel(int levelID) {
    string levelName;
    if (ENABLE_EDITOR) {
        levelName = "level_" + ofToString(levelID);
    } else if (!ENABLE_EDITOR) {
        levelName = "level_" + ofToString(levelID) + ".sav";
    }
    std::ifstream input(levelName.c_str());

    if (!input.good()) {
        levelName = "level_" + ofToString(levelID);
        input.open(levelName.c_str());
    }

    if (input.good()) {
        vector<Gravitator *>::iterator a = gravitator.begin();
        while (a != gravitator.end()) {
            delete *a;
            a = gravitator.erase(a);
        }
        vector<StrandedAstronaut *>::iterator b = strandedAstronaut.begin();
        while (b != strandedAstronaut.end()) {
            delete *b;
            b = strandedAstronaut.erase(b);
        }
        int listSize;
        float player_start_x, player_start_y;
        input >> listSize;
        input >> player_start_x >> player_start_y;
        player.pos.set(player_start_x, player_start_y);
        for(int i = 0; i < listSize; i++) {
            float x, y;
            int r, m, gR, size;
            string type;
            input >> x >> y >> r >> m >> gR >> type >> size;
            if (type == "planet") {
                gravitator.push_back(new Planet(ofVec2f(x, y), r, m, gR));
            } else if (type == "sun") {
                gravitator.push_back(new Sun(ofVec2f(x, y), r, m, gR));
            } else if (type == "blackhole") {
                gravitator.push_back(new BlackHole(ofVec2f(x, y), r, m, gR));
            } else if (type == "comet") {
                vector <ofVec2f> path;
                for (int k = 0; k < size; k++) {
                    ofVec2f point;
                    input >> point.x >> point.y;
                    path.push_back(point);
                }
                gravitator.push_back(new Comet(ofVec2f(x, y), r, path));
            } else if (type == "strandedastronaut") {
                strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(x, y), &gravitator, &strandedAstronaut, &gui));
            }
        }
        totalCrew = strandedAstronaut.size();
        vector<GUI *>::iterator c = gui.begin();
        while (c != gui.end()) {
            delete *c;
            c = gui.erase(c);
        }
        gui.push_back(new GUI());
        levelState = "loaded " + ofToString(levelID) + ".";
        WON_LEVEL = false;
        if (strandedAstronaut.size() > 0) {
            LEVEL_HAS_ASTRONAUTS    = true;
        } else {
            LEVEL_HAS_ASTRONAUTS    = false;
        }
        input.close();
    } else {
        levelState = "That level doesn't exist.";
        gravitator.clear();
        strandedAstronaut.clear();
        gui.clear();        /// NOTE (Aaron#9#): Don't forget to remove this later.
    }
}
