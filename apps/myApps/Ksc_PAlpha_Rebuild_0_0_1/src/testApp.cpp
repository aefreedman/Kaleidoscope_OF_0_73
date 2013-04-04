#include "testApp.h"
#include <fstream>
#define nl '\n'
#define screen_width 1280
#define screen_height 720
#define dt 1.0/60.0
#define spacer "  >>  "
#define bar "  ||  "
#define gap "   "

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofEnableAlphaBlending();



    player                          = Player(ofVec2f(300,300), &gravitator, &strandedAstronaut, &gui);
    clickState                      = "play mode";
    levelState                      = "Working from scratch.";
    new_gravitator_type             = "";
    planet_base_m                   = 1000;
    planet_mass_multiplier          = 250;
    CAN_EDIT_LEVEL                  = false;
    camera_lerp_speed               = 4; /// NOTE (Aaron#9#): This should change depending on player velocity
    camera_pos.set(0, 0, .5);
    view_scale_target               = .25;
    view_scale                      = 1;
    default_view_scale              = 1;
    view_lerp_speed                 = 4;
    map_view_scale_target           = .25;

    ///Starting level
    importLevel(0);
    gui.push_back(new GUI());

    ///Testing sound system
    jupiterSound.loadSound("Jupiter.mp3");
    jupiterSound.setLoop(true);
    jupiterSound.play();
    backgroundSound.loadSound("background.wav");
    backgroundSound.setLoop(true);
    backgroundSound.setVolume(0.25);
    backgroundSound.play();

    background.loadImage("bg.png");
}

//--------------------------------------------------------------
void testApp::update() {
    if (clickState != "play mode") {
        PAUSE = true;
    }
    if (!PAUSE) {
        player.update();
        for (int i = 0; i < gravitator.size(); i++) {
            gravitator[i]->update();
        }
        for (int i = 0; i < strandedAstronaut.size(); i++) {
            strandedAstronaut[i]->id = i;
            strandedAstronaut[i]->update();
        }
        for (int i = 0; i < gui.size(); i++) {
            gui[i]->update();
        }
    }

    /// TODO (Aaron#1#): Map view needs to account for camera position when scaling
    camera_pos.interpolate(camera_target, camera_lerp_speed * dt);
    player.camera_pos = camera_pos;
    player.camera_target = camera_target;
    if (player.OFF_SCREEN == true && clickState == "play mode") {
        moveCamera(player.camera_move_direction);
        player.OFF_SCREEN = false;
    }
    if (MAP_VIEW) {
        view_scale = ofLerp(view_scale, map_view_scale_target, view_lerp_speed * dt);
    } else {
        view_scale = ofLerp(view_scale, default_view_scale, view_lerp_speed * dt);
    }
}

void testApp::moveCamera(string direction) {
    ofVec2f target;
    if (direction == "up") {
        target.set(0, -screen_height);
    } else if (direction == "down") {
        target.set(0, screen_height);
    } else if (direction == "left") {
        target.set(-screen_width, 0);
    } else if (direction == "right") {
        target.set(screen_width, 0);
    }

    target += camera_target;
    camera_target.x = target.x;
    camera_target.y = target.y;
    camera_target.z = 0;
}

//--------------------------------------------------------------
void testApp::draw() {
    ofPushMatrix();
    ofTranslate(-camera_pos);
    //ofRotate(50, 0, 0, 1);
    ofScale(view_scale, view_scale, 1);
    ofSetColor(255,255,255);
    if (MAP_VIEW) {
        ofBackground(0, 0, 0);
    } else {

        background.draw(camera_pos);
    }

    for (int i = 0; i < gravitator.size(); i++) {
        gravitator[i]->draw();
    }
    for (int i = 0; i < gui.size(); i++) {
        gui[i]->draw();
    }
    for (int i = 0; i < strandedAstronaut.size(); i++) {
        strandedAstronaut[i]->draw();
    }
    player.draw();
    ofPopMatrix();

    /// TODO (Aaron#9#): Move level editor into own class
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

        //ofSetColor(0,255,0);
        //ofDrawBitmapString("press 'h' to toggle habitability. (right now it's " + ofToString(planetHabitability) + ".)", 40,100);
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
    ofSetColor(0, 255, 0);
    string top_text = "";
    top_text.append("level " + ofToString(levelID));
    top_text.append(spacer);
    top_text.append(clickState);
    top_text.append(gap);
    if (clickState == "play mode") {
        top_text.append("[F1] to edit level");
        top_text.append(bar);
        top_text.append("[s] to place player");
        top_text.append(gap);
        top_text.append(ofToString(camera_pos, 2));
        top_text.append(gap);
        top_text.append(ofToString(camera_target));
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

    ofDrawBitmapString(top_text, 1, 10);
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

void testApp::addGravitator() {
    if (new_gravitator_type == "planet") {
        gravitator.push_back(new Planet((1 / view_scale) * (NEW_PLANET_POS + camera_pos), (1 / view_scale) * NEW_PLANET_R, NEW_PLANET_M, (1 / view_scale) * NEW_PLANET_GR));
    }
    if (new_gravitator_type == "sun") {
        gravitator.push_back(new Sun((1 / view_scale) * (NEW_PLANET_POS + camera_pos), (1 / view_scale) * NEW_PLANET_R, NEW_PLANET_M, (1 / view_scale) * NEW_PLANET_GR));
    }
    if (new_gravitator_type == "black hole") {
        gravitator.push_back(new BlackHole((1 / view_scale) * (NEW_PLANET_POS + camera_pos), (1 / view_scale) * NEW_PLANET_R, NEW_PLANET_M, (1 / view_scale) * NEW_PLANET_GR));
    }
    new_gravitator_type = "";
}

void testApp::addStrandedAstronaut(ofVec2f _pos) {
    strandedAstronaut.push_back(new StrandedAstronaut((1 / view_scale) * (_pos + camera_pos), &gravitator, &strandedAstronaut, &gui));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    switch (key) {
    case 'i':
        if (iddqd == 0) {
            iddqd = 1;
        }
        break;
    case 'd':
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
        CAN_EDIT_LEVEL = !CAN_EDIT_LEVEL;
        if (clickState == "play mode") {
            clickState = "edit mode";
        } else {
            clickState = "play mode";
            PAUSE = false;
        }
        break;
    case 'p':
        if (CAN_EDIT_LEVEL) {
            clickState = "placing gravitators";
            new_gravitator_type = "planet";
        }
        break;
    case 'a':
        if (CAN_EDIT_LEVEL) {
            clickState = "placing astronaut";
        }
        break;
    case 'A':
        if (CAN_EDIT_LEVEL) {
            strandedAstronaut.clear();
        }
        break;
    case 's':
        clickState = "placing player";
        player.setup();
        break;
    case OF_KEY_F5:
        exportLevel();
        break;
    case OF_KEY_F2:
        if (levelID > 0) {
            levelID--;
            importLevel(levelID);
        }
        break;
    case OF_KEY_F3:
        if (levelState != "That level doesn't exist.") {
            levelID++;
            importLevel(levelID);
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
        if (player.CAN_JETPACK && !player.TRAVERSING_PLANET) {
            player.jetpack(true);
            break;
        } else if (player.TRAVERSING_PLANET) {
            player.chargeJump();
            player.TRAVERSING_PLANET = true;
            break;
        }
    case OF_KEY_DOWN:
        if (player.CAN_JETPACK && !player.IN_GRAVITY_WELL) {
            //player.jetpack(false);
            break;
        }
        break;
    case OF_KEY_LEFT:
        if (player.TRAVERSING_PLANET) {
            player.traversePlanet(true);
            break;
        } else {
            player.rotateDirection(true);
            break;
        }
    case OF_KEY_RIGHT:
        if (player.TRAVERSING_PLANET) {
            player.traversePlanet(false);
            break;
        } else {
            player.rotateDirection(false);
            break;
        }
    case OF_KEY_F8:
        moveCamera("up");
        break;
    case '9':
        moveCamera("right");
        break;
    case '7':
        moveCamera("left");
        break;
    case '8':
        moveCamera("down");
        break;
    case 32:
        player.releaseAllAstronauts();
        break;
    case '=':
        player.damp += 0.01;
        break;
    case '-':
        player.damp -= 0.01;
        break;
    case 'm':
        MAP_VIEW = !MAP_VIEW;
        PAUSE = !PAUSE;
        break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    switch (key) {
    case 'a':
        break;
    case 'd':
        break;
    case OF_KEY_UP:
        if (player.IN_GRAVITY_WELL) {
            player.jump();
            break;
        } else {
            player.CAN_JETPACK = true;
            break;
        }
    case 32:
        break;
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
    if (clickState == "placing player") {
        player.pos.set(x + camera_pos.x, y + camera_pos.y);
    }

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
    if (clickState == "edit mode") {
        ofVec2f mouse_pos;
        mouse_pos.set(x, y);
        mouse_pos += camera_pos;
        for (int i = 0; i < gravitator.size(); i++) {
            ofVec2f g_pos;
            g_pos.set(gravitator[i]->pos);
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
void testApp::mousePressed(int x, int y, int button) {
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
        start.set(NEW_COMET_POS + camera_pos);
        temp.push_back(start);
        gravitator.push_back(new Comet(NEW_COMET_POS, NEW_COMET_R, temp));
        clickState = "placing path";
    }
    if (clickState == "placing path") {
        gravitator[gravitator.size()-1]->pathPoints.push_back(ofVec2f(x + camera_pos.x, y + camera_pos.y));
    }
    if (clickState == "placing player") {
        player.pos.set(ofVec2f(mouseX + camera_pos.x, mouseY + camera_pos.y));
        player.starting_pos.set(player.pos);
        clickState = "play mode";
    }
    if (clickState == "placing astronaut") {
        addStrandedAstronaut(ofVec2f(mouseX, mouseY));
        clickState = "edit mode";
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
    if (clickState == "setting size") {
        NEW_PLANET_R = ofDist(x, y, NEW_PLANET_POS.x, NEW_PLANET_POS.y);
        clickState = "setting grav";
    }

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}

void testApp::exportLevel() {
    while (true) {
        string levelName = "level_" + ofToString(levelID);
        std::ifstream input(levelName.c_str());
        if  (input.good()) {
            std::ofstream output(levelName.c_str());
            output << gravitator.size() + strandedAstronaut.size() << std::endl;
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
        }
    }

}
/// NOTE (Aaron#9#): Loading levels causes a small memory leak (vectors are only cleared)

void testApp::importLevel(int levelID) {
    std::ifstream input(("level_" + ofToString(levelID)).c_str());
    if (input.good()) {
        gravitator.clear();
        strandedAstronaut.clear();
        int listSize;
        input >> listSize;
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
        levelState = "loaded " + ofToString(levelID) + ".";
    } else {
        levelState = "That level doesn't exist.";
        gravitator.clear();
        strandedAstronaut.clear();
        gui.clear();        /// NOTE (Aaron#9#): Don't forget to remove this later.
    }
}
