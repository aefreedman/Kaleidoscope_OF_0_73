#include "GameScreen.h"

#include <fstream>

#define nl '\n'
#define dt 1.0/60.0
#define spacer "  >>  "
#define bar "  ||  "
#define gap "   "

//--------------------------------------------------------------
GameScreen::GameScreen() : Screen() {}

GameScreen::~GameScreen() {}

void GameScreen::setup() {
    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    generateStars();
    camera_pos.set(0, 0, 0);
    camera_target.set(0, 0, 0);
    USING_LEVEL_EDITOR              = false;
    CAMERA_SCALING                  = false;
    WON_LEVEL                       = false;
    MAP_VIEW                        = false;
    GAME_OVER                       = false;
//    const float default_view_scale              = 1.0;
    view_scale                      = 1;
    view_scale_target               = 1;
    background.loadImage("ART/bg.png");
    fadeIn                          = GUIFadeIn(camera_pos);
    level_over_timer_start          = 3.0;
    level_over_timer                = level_over_timer_start;

    ///------------------------------
    /// YOU CAN CHANGE THESE
    ///------------------------------

    player_start_pos.set(ofGetWidth() / 2, ofGetHeight() / 2);
    planet_base_m                   = 1000;
    planet_mass_multiplier          = 250;
    camera_lerp_speed               = 4; /// NOTE (Aaron#9#): This should change depending on player velocity
    view_lerp_speed                 = 4;
    map_view_scale_target           = .25;
    levelID                         = 20;

    CONTINUOUS_CAMERA               = true;
    MOVE_MESSAGES                   = false;
    ENABLE_EDITOR                   = true;

    ///------------------------------
    /// DON'T CHANGE THESE
    ///------------------------------
    player                          = Player(player_start_pos, &gravitator, &strandedAstronaut, &gui);
    clickState                      = "play mode";
    levelState                      = "Working from scratch.";
    new_gravitator_type             = "";
    new_astronaut_name              = "unnamed";
    if (LOAD_WITH_SOUND) {
        loadSound();
        player.loadSound();
    }
    importLevel(levelID);

    planetRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 128); //declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
    planetRenderer->loadTexture("ART/planets.png", 512, GL_NEAREST); // load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    nautRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 64);             /// declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
    nautRenderer->loadTexture("ART/nauts.png", 512, GL_NEAREST);                /// load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    ofEnableAlphaBlending(); // turn on alpha blending. important!

    //HUD

    O2frame.loadImage("ART/O2_frame.png");
    O2bar.loadImage("ART/O2_bar.png");
    map.loadImage("ART/map3.png");

}

void GameScreen::generateStars() {
    stars.clear();
    for (int i = 0; i < number_of_stars; i++) {
        int screens_squared = 10;
        int initial_blink_period = 200;
        stars.push_back(ofVec4f(
                                ofRandom(                       /// x
                                        -ofGetWidth(),
                                        ofGetWidth()
                                        ) * screens_squared,
                                ofRandom(                       /// y
                                         -ofGetHeight(),
                                        ofGetHeight()
                                        ) * screens_squared,
                                ofRandom (-10, 10),             /// z
                                ofRandom(initial_blink_period)  /// w (used for timing)
                                )
                        );
        stars_dark.push_back(ofVec4f(
                                    ofRandom(                  /// x
                                            -ofGetWidth(),
                                            ofGetWidth()
                                            ) * screens_squared,
                                    ofRandom(                 /// y
                                            -ofGetHeight(),
                                            ofGetHeight()
                                            )* screens_squared,
                              ofRandom (-10, 10),               /// z
                              ofRandom(initial_blink_period)    /// w (used for timing)
                                )
                             );
    }
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

void GameScreen::getState() {
    PAUSE = false;
    if (MAP_VIEW) {
        PAUSE = true;
    } else {
    }
    if (PAUSE) {
        CAN_MOVE_CAM = true;
    }
    if (ENABLE_EDITOR) {
        if (USING_LEVEL_EDITOR) {
            CAN_MOVE_CAM = true;
            PAUSE = true;
            if (clickState == "play mode" || clickState == "edit mode") {
                PLACING_SOMETHING = false;
            } else {
                PLACING_SOMETHING = true;
            }
            if (PLACING_SOMETHING) {
                //CAN_MOVE_CAM = false;
            }
        }
    }
    if (LEVEL_HAS_ASTRONAUTS) {
        if (strandedAstronaut.size() == 0) {
            if (player.IS_DEAD) {
                WON_LEVEL = true;
            }
        } else if (player.IS_DEAD) {
            FREEZE_PLAYER = true;
            level_over_timer = countdownTimer(level_over_timer);
            if (AN_ASTRONAUT_DIED) {
                level_over_timer = level_over_timer_start;
                AN_ASTRONAUT_DIED = false;
            }
            if (level_over_timer <= 0) {
                metric_playerDeaths.push_back(ofVec4f(player.pos.x, player.pos.y, levelID, ofGetElapsedTimef()));
                metric_playerDeaths_cause.push_back(player.gravitator_type);
                //metric_playerJetpackUses.push_back
                reset();
            }
        }
    }
    if (!LEVEL_HAS_ASTRONAUTS) {
        if (player.IS_DEAD) {
            WON_LEVEL = true;
        }
    }
    if (WON_LEVEL) {
        if (!GAME_OVER) {
            levelID++;
            importLevel(levelID);
            reset();
            fadeIn.setActive(true);
            FREEZE_PLAYER = false;
            generateStars();
        } else {
            PAUSE = true;
        }
    }
}

void GameScreen::update() {
    getState();
    if (!PAUSE) {
        if (!FREEZE_PLAYER) {
            player.update();
        }
        fadeIn.update();
        for (int i = 0; i < gravitator.size(); i++) {
            gravitator[i]->update();
        }
        for (int i = 0; i < strandedAstronaut.size(); i++) {
            strandedAstronaut[i]->id = i;
            strandedAstronaut[i]->update();
            if (strandedAstronaut[i]->IS_DEAD) {
                AN_ASTRONAUT_DIED = true;
                if (strandedAstronaut[i]->FOLLOWING_PLAYER) {
                    player.releaseAllAstronauts(false);
                }
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
            if ((gui[i]->pos.x > ofGetWidth() + camera_target.x - 50 || gui[i]->pos.y > ofGetHeight() + camera_target.y + 30 || gui[i]->pos.x < camera_target.x - 50 || gui[i]->pos.y < camera_target.y + 30) && camera_pos.squareDistance(camera_target) < 10) {
                gui[i]->pos.interpolate(player.pos, 10 * dt);
            }
        }
    }
    camera();
    fadeIn.pos.interpolate(camera_target, camera_lerp_speed * dt);
    renderSprites();
    player.camera_pos = camera_pos;
    player.camera_target = camera_target;
}

void GameScreen::camera() {
    /// TODO (Aaron#1#): Map view needs to account for camera position when scaling
    if (!PAUSE) {
        setCameraTarget(player.pos);
    }
    view_scale = ofLerp(view_scale, view_scale_target, view_lerp_speed * dt);

    if (view_scale >= view_scale_target * 0.95 && view_scale <= view_scale_target * 1.05) {
        CAMERA_SCALING = false;
    }   else {
        CAMERA_SCALING = true;
    }
    camera_pos.interpolate(camera_target, camera_lerp_speed * dt);
}

void GameScreen::setCameraTarget(ofVec2f target) {
    camera_target.x = (target.x * view_scale_target) - ofGetWidth()/2;
    camera_target.y = (target.y * view_scale_target) - ofGetHeight()/2;
}

void GameScreen::moveCameraTarget(ofVec2f direction) {
    camera_target += direction;
}

void GameScreen::renderSprites() {
    planetRenderer->clear(); // clear the sheet
    for(int i = 0; i < gravitator.size(); i++) {
        float scaleFactor;
        if (gravitator[i]->type == "comet") {
            scaleFactor = 2;
        } else if (gravitator[i]-> type == "planet") {
            scaleFactor = 2.0*gravitator[i]->gR/128.0;
            planetRenderer->addCenteredTile(&gravitator[i]->anim2,gravitator[i]->pos.x,gravitator[i]->pos.y,-1,F_NONE,scaleFactor,255,255,255,255);
            scaleFactor = 4.0*gravitator[i]->r/120.0;
        } else if (gravitator[i]->type == "sun") {
            scaleFactor = 2 * gravitator[i]->r/128.0;
        } else if (gravitator[i]->type == "blackhole") {
            scaleFactor = 2 * gravitator[i]->gR/128.0;
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

void GameScreen::drawGUI() {
    /// Use local (screen) postions
    if (!MAP_VIEW) {
        ofPushMatrix();
        ofFill();
        ofSetColor(255, 255, 255);
        for (int i = 0; i < totalCrew; i++) {
            if (i < strandedAstronaut.size()) {
                ofSetColor(255, 255, 255);
                ofRect(30+(12*i) , ofGetHeight() - map.height + 34, 7,7);
            } else {
                ofSetColor(223, 42, 99);
                ofRect(30+(12*i) ,  ofGetHeight() - map.height + 34, 7,7);
            }
        }
        int x = ofGetWidth() - 53;
        int y = ofGetHeight() - 26;
        float o2_percent = player.oxygen / player.max_oxygen;
        ofSetColor(200 - (200 * o2_percent), 211 * o2_percent, 222 * o2_percent);
        ofRect(ofPoint(x, y), 20, -136 * o2_percent);

        int percentOut = 400 * (1 - ( player.oxygen / player.max_oxygen));

        ofSetColor(255,255,255,255);
        O2frame.draw(ofGetWidth() - O2frame.width - 20, ofGetHeight() - O2frame.height - 20);
        map.draw(0 , ofGetHeight() - map.height);
        ofPopMatrix();
    }
}

void GameScreen::draw() {
    /// LAYER 0 -- Background (CAMERA; !ZOOM)
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(-camera_pos);
    background.draw(camera_pos);
    ofPopMatrix();

    /// LAYER 1 -- Background (CAMERA && ZOOM)
    ofPushMatrix();
    ofTranslate(-camera_target);
    ofScale(view_scale, view_scale, 1);
    ofSetColor(255,255,255,50);
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(-camera_pos);
    ofScale(view_scale, view_scale, 1);
    for (int i = 0; i < stars.size(); i++) {
        int blink_brightness = 25;
        int dark_star_brightness = 125;
        int blink_time = 10;
        int blink_period = 200;
        int num_redGiants = 30;
        int num_dwarves = 30;
        ofColor starLight(ofColor::white);
        if (stars[i].x > camera_pos.x && stars[i].x < camera_pos.x + ofGetWidth() && stars[i].y > camera_pos.y && stars[i].y < camera_pos.y + ofGetHeight()) {
            if (stars[i].w < blink_time) {
                stars[i].w += 1;
                starLight.setBrightness(blink_brightness);
            } else if (stars[i].w >= blink_time) {
                stars[i].w += 1;
                starLight.setBrightness(ofRandom(200, 255));
                if (stars[i].w > blink_period) {
                    stars[i].w = ofRandom (blink_period);
                }
            }
            if (i < num_redGiants) {
                starLight.r = 255;
                starLight.g = 125;
                starLight.b = 0;
            }
            if (i > num_redGiants && i < num_redGiants + num_dwarves) {
                starLight.r = 0;
                starLight.g = 231;
                starLight.b = 255;
            }
            ofSetColor(starLight);
            ofRect(stars[i].x, stars[i].y, stars[i].z, 2, 2);
        }
        starLight.setBrightness(dark_star_brightness);
        if (stars_dark[i].x > camera_pos.x && stars_dark[i].x < camera_pos.x + ofGetWidth() && stars_dark[i].y > camera_pos.y && stars_dark[i].y < camera_pos.y + ofGetHeight()) {
            if (stars_dark[i].w < blink_time) {
                stars_dark[i].w += 1;
                starLight.setBrightness(50);
            } else if (stars_dark[i].w >= blink_time) {
                stars_dark[i].w += 1;
                starLight.a = dark_star_brightness;
                if (stars_dark[i].w > blink_period) {
                    stars_dark[i].w = ofRandom (blink_period);
                }
            }
            ofSetColor(starLight);
            ofRect(stars_dark[i].x, stars_dark[i].y, stars_dark[i].z, 2, 2);
        }
    }
    ofPopMatrix();

    /// LAYER 2 -- GameObjects (CAMERA && ZOOM)
    ofPushMatrix();
    ofTranslate(-camera_pos);
    ofScale(view_scale, view_scale, 1);
    ofSetColor(255,255,255);

    planetRenderer -> draw();

    for (int i = 0; i < gravitator.size(); i++) {
        gravitator[i]->draw();
        if (gravitator[i]->type == "comet") {
            if (USING_LEVEL_EDITOR) {
                gravitator[i]->drawPath();
            }
        }
    }

    for (int i = 0; i < gui.size(); i++) {
        gui[i]->draw();
    }
    for (int i = 0; i < strandedAstronaut.size(); i++) {
        strandedAstronaut[i]->draw();
    }
    player.draw();
    nautRenderer -> draw();

    fadeIn.draw();/// TODO (Aaron#1#): FadeIn needs to scale
    ofPopMatrix();

    /// LAYER 3 -- GUI (!CAMERA && !ZOOM)
    drawGUI();
    drawLevelEditorGUI();
}

void GameScreen::drawLevelEditorGUI() {
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
        top_text.append(ofToString(camera_pos, 2));
        top_text.append(gap);
        top_text.append(ofToString(camera_target, 2));
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

    if (ENABLE_EDITOR) {
        ofPushMatrix();
        ofSetColor(0, 255, 0);
        ofDrawBitmapString(top_text, 1, 10);
        ofPopMatrix();
    }

    ///FLOATING MOUSE TEXT ----------------------------------
    if (clickState != "play mode") {
        ofVec2f draw_pos;
        draw_pos.x = mouseX + 20;
        draw_pos.y = mouseY + 20;
        int draw_y2 = draw_pos.y + 15;

        if (clickState != "edit mode") {
            string mouse_text = "";
            mouse_text.append("placing: ");
            if (clickState == "placing gravitators") {
                mouse_text.append(new_gravitator_type);
            }
            if (clickState == "placing player") {
                mouse_text.append("player");
            }
            if (clickState == "placing astronaut") {
                mouse_text.append("astronaut: ");
                mouse_text.append(new_astronaut_name);
            }
            if (clickState == "placing comet") {
                mouse_text.append("comet");
            }
            if (clickState == "placing path") {
                mouse_text.append("comet path");
            }
            ofDrawBitmapString(mouse_text, draw_pos.x, draw_pos.y);
        }

        string placement_text = "";
        if (clickState == "placing gravitators") {
            placement_text.append("click & drag to make gravitator \n");
            placement_text.append("press [PAGE UP] to cycle placement type");
        } else if (clickState == "setting size") {
            placement_text = "release to set size.";
        } else if (clickState == "setting grav") {
            placement_text = "click to set gravity range.";
        } else if (clickState == "placing player") {
            placement_text = "click to set player location";
        } else if (clickState == "placing path") {
            placement_text = "[c] to stop placing path";
        } else if (clickState == "placing astronaut") {
            placement_text == "[a] to stop placing astronauts";
        } else placement_text = "";
        ofDrawBitmapString(placement_text, draw_pos.x, draw_y2);

        if (clickState == "edit mode") {
            int x = 50;
            int y = 100;
            string info = "";
            info.append("[g] to place gravitators \n");
            info.append("[C] to clear gravitators \n\n");
            info.append("[c] to place comet \n");
            info.append("[a] to place astronaut \n");
            info.append("[A] to clear astronauts \n");
            ofDrawBitmapString(info, draw_pos.x, draw_pos.y);
        }
    }
}

void GameScreen::reset() {
    importLevel(levelID);
    player.setup();
    fadeIn.setup();
    level_over_timer = level_over_timer_start;
    FREEZE_PLAYER = false;
    GAME_OVER = false;
}

void GameScreen::addGravitator(ofVec2f pos, int r, int gR, int m) {
    pos = getGlobalPosition(pos);
    r = r / view_scale;
    gR = gR / view_scale;
    if (new_gravitator_type == "planet") {
        gravitator.push_back(new Planet(pos, r, m, gR));
    }
    if (new_gravitator_type == "sun") {
        gravitator.push_back(new Sun(pos, r, m, gR));
    }
    if (new_gravitator_type == "black hole") {
        gravitator.push_back(new BlackHole(pos, r, m, gR));
    }
    new_gravitator_type = "";
}

void GameScreen::addStrandedAstronaut(ofVec2f _pos, string _name = "unnamed") {
    if (_name == "unnamed") {
        strandedAstronaut.push_back(new StrandedAstronaut(getGlobalPosition(_pos), StrandedAstronaut::UNNAMED, &gravitator, &strandedAstronaut));
    }
    if (_name == "tutorial one") {
        strandedAstronaut.push_back(new StrandedAstronaut(getGlobalPosition(_pos), StrandedAstronaut::TUTORIAL_ONE, &gravitator, &strandedAstronaut));
    }
    if (_name == "tutorial two") {
        strandedAstronaut.push_back(new StrandedAstronaut(getGlobalPosition(_pos), StrandedAstronaut::TUTORIAL_TWO, &gravitator, &strandedAstronaut));
    }
    if (_name == "tutorial three") {
        strandedAstronaut.push_back(new StrandedAstronaut(getGlobalPosition(_pos), StrandedAstronaut::TUTORIAL_THREE, &gravitator, &strandedAstronaut));
    }
    strandedAstronaut[strandedAstronaut.size()-1]->level = levelID;
}

ofVec2f GameScreen::getLocalPosition(ofVec2f global_pos) {
    ofVec2f local_pos;
    local_pos = (global_pos * view_scale) - camera_pos;
    return local_pos;
}

ofVec2f GameScreen::getGlobalPosition(ofVec2f local_pos) {
    ofVec2f global_pos;
    global_pos = (local_pos + camera_pos) / view_scale;
    return global_pos;
}

//--------------------------------------------------------------
void GameScreen::keyPressed(int key) {
    switch (key) {
    case 'i':
        if (iddqd == 0) {
            iddqd = 1;
            break;
        }
        break;
    case 'd':
        if (iddqd == 1 || iddqd == 2) {
            iddqd++;
            break;
        }
        if (iddqd == 4) {
            player.GOD_MODE = !player.GOD_MODE;
            iddqd = 0;
            break;
        }
        break;
    case 'q':
        if (iddqd == 3) {
            iddqd = 4;
            break;
        }
        break;
    case OF_KEY_F1:
        if (ENABLE_EDITOR) {
            USING_LEVEL_EDITOR = !USING_LEVEL_EDITOR;
            if (clickState == "play mode") {
                clickState = "edit mode";
            } else {
                clickState = "play mode";
            }
        }
        break;
    case 'g':
        if (USING_LEVEL_EDITOR && clickState == "edit mode") {
            clickState = "placing gravitators";
            new_gravitator_type = "planet";
        }
        break;
    case 'a':
        if (USING_LEVEL_EDITOR && clickState == "edit mode") {
            clickState = "placing astronaut";
            break;
        }
        if (clickState == "placing astronaut") {
            clickState = "edit mode";
            break;
        }
        break;
    case 'A':
        if (USING_LEVEL_EDITOR) {
            strandedAstronaut.clear();
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
        if (USING_LEVEL_EDITOR) {
            if (clickState == "placing path") {
                clickState = "edit mode";
            } else {
                clickState = "placing comet";
            }
        }
        break;
    case 'C':
        if (USING_LEVEL_EDITOR) {
            gravitator.clear();
        }
        break;
    case OF_KEY_UP:
        if (!player.IS_DEAD) {
            if (player.CAN_JETPACK && !player.TRAVERSE_MODE && !player.DEATH_ANIMATION) {
                player.jetpack(true);
                break;
            } else if (player.TRAVERSE_MODE) {
                if (player.ROTATE_LEFT || player.ROTATE_RIGHT) {
                    //player.ROTATE_LEFT = false;
                    //player.ROTATE_RIGHT = false;
                }
                player.chargeJump();
                break;
            }
        }
        break;
    case OF_KEY_PAGE_UP:
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
        if (clickState == "placing astronaut") {
            if (new_astronaut_name == "") {
                new_astronaut_name = "unnamed";
                break;
            }
            if (new_astronaut_name == "unnamed") {
                new_astronaut_name = "tutorial one";
                break;
            }
            if (new_astronaut_name == "tutorial one") {
                new_astronaut_name = "tutorial two";
                break;
            }
            if (new_astronaut_name == "tutorial two") {
                new_astronaut_name = "tutorial three";
                break;
            }
            if (new_astronaut_name == "tutorial three") {
                new_astronaut_name = "unnamed";
                break;
            }
        }
    case OF_KEY_LEFT:
        if (!player.CHARGING_JUMP) {player.ROTATE_LEFT = true;}
        break;
    case OF_KEY_RIGHT:
        if (!player.CHARGING_JUMP) {player.ROTATE_RIGHT = true;}
        break;
    case 32:
        if (!player.IS_DEAD) {
            if (player.CAN_JETPACK && !player.TRAVERSE_MODE && !player.DEATH_ANIMATION) {
                player.jetpack(true);
                break;
            } else if (player.TRAVERSE_MODE) {
                player.chargeJump();
                break;
            }
        }
        break;
    case 'm':
        if (ENABLE_EDITOR) {
            if (!MAP_VIEW) {
                view_scale_target = map_view_scale_target;
                setCameraTarget(player.pos);
            } else if (MAP_VIEW) {
                view_scale_target = default_view_scale;
                setCameraTarget(player.pos);

            }
            MAP_VIEW = !MAP_VIEW;
        }
        break;
    case 'R':
        reset();
        break;
    case 'z':
        for (int i = 0; i < strandedAstronaut.size(); i++) {
            strandedAstronaut[i]->FOLLOWING_ASTRONAUT = false;
        }
        break;
    case OF_KEY_INSERT:
        screenshot();
        break;
    case 's':
        player.KILL_PLAYER = true;
        player.releaseAllAstronauts(false);
        break;
    }
}

//--------------------------------------------------------------
void GameScreen::keyReleased(int key) {
    switch (key) {
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
            if (!ENABLE_EDITOR) {
                exportLevel();
            }
            break;
        } else {
            player.CAN_JETPACK = true;
            player.CHARGING_JUMP = false;
            break;
        }
    case OF_KEY_LEFT:
        if (player.ROTATE_LEFT && !player.DEATH_ANIMATION) {
            player.anim = idle;
            player.fxJetpackLoop.stop();
        }
            player.ROTATE_LEFT = false;
        break;
    case OF_KEY_RIGHT:
        if (player.ROTATE_RIGHT && !player.DEATH_ANIMATION) {
            player.anim = idle;
            player.fxJetpackLoop.stop();
        }
            player.ROTATE_RIGHT = false;
        break;
    }
}

//--------------------------------------------------------------
void GameScreen::mouseMoved(int x, int y ) {
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void GameScreen::mouseDragged(int x, int y, int button) {
    if (CAN_MOVE_CAM && (button == 1 || button == 2)) {
        setCameraTarget(getGlobalPosition(ofVec2f(x, y)));
    }

    if (clickState == "edit mode" && button == 0) {
        ofVec2f mouse_pos;
        mouse_pos = getGlobalPosition(ofVec2f(x, y));
        for (int i = 0; i < gravitator.size(); i++) {
            ofVec2f g_pos;
            g_pos.set(gravitator[i]->pos / view_scale);
            /// NOTE (Aaron#1#): This needs to be updmated to account for view_scale
            if (g_pos.x > camera_pos.x && g_pos.x < camera_pos.x + ofGetWidth() && g_pos.y > camera_pos.y && g_pos.y < camera_pos.y + ofGetHeight()) {
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
    if (button == 0) {
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
            addGravitator(NEW_PLANET_POS, NEW_PLANET_R, NEW_PLANET_GR, NEW_PLANET_M);
            clickState = "edit mode";
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
            player.pos.set(getGlobalPosition(ofVec2f(mouseX, mouseY)));
            player.starting_pos.set(player.pos);
            clickState = "edit mode";
        }
        if (clickState == "placing astronaut") {
            addStrandedAstronaut(ofVec2f(mouseX, mouseY), new_astronaut_name);
        }
    }
}

//--------------------------------------------------------------
void GameScreen::mouseReleased(int x, int y, int button) {
    if (button == 0) {
        if (clickState == "setting size") {
            NEW_PLANET_R = ofDist(x, y, NEW_PLANET_POS.x, NEW_PLANET_POS.y);
            clickState = "setting grav";
        }
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
            levelName = "data/levels/level_" + ofToString(levelID);
        }
        if (!ENABLE_EDITOR) {
            levelName = "data/levels/saves/level_" + ofToString(levelID) + ".sav";
        }
        std::ifstream input(levelName.c_str());
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
            << strandedAstronaut[i]->thisAstronautIs << ' '
            << 0 << ' '
            << 0 << ' '
            << strandedAstronaut[i]->type << ' '
            << 0 << ' '
            << std::endl;
        }
        levelState = ofToString(levelName) + " saved";
        break;
    }
}

void GameScreen::importLevel(int levelID) {
    string levelName;
    if (ENABLE_EDITOR) {
        levelName = "data/levels/level_" + ofToString(levelID);
    } else if (!ENABLE_EDITOR) {
        levelName = "data/levels/saves/level_" + ofToString(levelID) + ".sav";
    }
    std::ifstream input(levelName.c_str());

    if (!input.good()) {
        levelName = "data/levels/level_" + ofToString(levelID);
        input.open(levelName.c_str());
        if (!input.good()) {
            if (!ENABLE_EDITOR) {
                GAME_OVER = true;
                return;
            } else {
                levelName = "data/levels/level_" + ofToString(levelID + 1);
                std::ofstream output(levelName.c_str());
                output << 0 << std::endl;
                output << 0 << ' ' << 0 << std::endl;
                input.open(levelName.c_str());
            }
        }
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
        player.starting_pos.set(player_start_x, player_start_y);
        player.pos.set(player.starting_pos);
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
                if (r == 0) {
                    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(x, y), StrandedAstronaut::UNNAMED, &gravitator, &strandedAstronaut));
                }
                if (r == 1) {
                    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(x, y), StrandedAstronaut::TUTORIAL_ONE, &gravitator, &strandedAstronaut));
                }
                if (r == 2) {
                    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(x, y), StrandedAstronaut::TUTORIAL_TWO, &gravitator, &strandedAstronaut));
                }
                if (r == 3) {
                    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(x, y), StrandedAstronaut::TUTORIAL_THREE, &gravitator, &strandedAstronaut));
                }
                strandedAstronaut[strandedAstronaut.size()-1]->level = levelID;
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
        camera_pos.set(ofVec2f(player.pos.x - ofGetWidth()/2, player.pos.y - ofGetHeight()/2));
        fadeIn.pos.set(ofVec2f(player.pos.x - ofGetWidth()/2, player.pos.y - ofGetHeight()/2));
        input.close();
    } else {
        levelState = "That level doesn't exist.";
        gravitator.clear();
        strandedAstronaut.clear();
        gui.clear();        /// NOTE (Aaron#9#): Don't forget to remove this later.
    }
}

void GameScreen::exportSessionData() {
    ofxXmlSettings sessionData;
    sessionData.addTag("sessionData");
    sessionData.pushTag("sessionData");
    sessionData.addValue("total_playtime", ofGetElapsedTimef());
    sessionData.addTag("deaths");
    sessionData.pushTag("deaths");
    sessionData.addValue("total_deaths", ofToString(metric_playerDeaths.size()));
    for (int i = 0; i < metric_playerDeaths.size(); i++) {
        sessionData.addTag("death");
        sessionData.pushTag("death", i);
        sessionData.addValue("x", ofToString(metric_playerDeaths[i].x));
        sessionData.addValue("y", ofToString(metric_playerDeaths[i].y));
        sessionData.addValue("level", ofToString(metric_playerDeaths[i].z));
        sessionData.addValue("elapsedTime", metric_playerDeaths[i].w);
        sessionData.addValue("cause", metric_playerDeaths_cause[i]);
        sessionData.popTag();
    }
    sessionData.popTag();
    sessionData.popTag();
    sessionData.saveFile("sessionData/sessionData_" + ofToString(ofGetMonth()) + "_" + ofToString(ofGetDay()) + "_" + ofToString(ofGetHours()) + "_" + ofToString(ofGetMinutes()) + ".xml");
}

void GameScreen::exit() {
    exportSessionData();
}

void GameScreen::screenshot() {
    string filename = "screenshots/screenshot_" + ofToString(ofGetMonth()) + ofToString(ofGetWeekday()) + "_" + ofToString(ofGetHours()) + "_" + ofToString(ofGetMinutes()) + ".png";
    ofSaveScreen(filename);
}

bool GameScreen::isGameOver() const {
    return GAME_OVER;
}

int GameScreen::getLevel() const {
    return levelID;
}

void GameScreen::setLevel(int level_number) {
    levelID = level_number;
}

void GameScreen::setGameOver(bool _gameOver) {
    GAME_OVER = _gameOver;
}
