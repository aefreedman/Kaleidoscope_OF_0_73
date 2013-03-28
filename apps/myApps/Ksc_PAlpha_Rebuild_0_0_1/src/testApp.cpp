#include "testApp.h"
#include <fstream>
#define nl '\n'
#define screen_width 1280
#define screen_height 720
#define dt 1.0/60.0
#define spacer "  >>  "
#define gap "   "

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);

    player                          = Player(ofVec2f(300,300), &gravitator, &strandedAstronaut);
    clickState                      = "play mode";
    levelState                      = "Working from scratch.";
    new_gravitator_type             = "";
    planet_base_m                   = 1000;
    planet_mass_multiplier          = 250;
    CAN_EDIT_LEVEL                  = false;

    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(screen_width / 2, screen_height / 2), &gravitator, &gui));
    gravitator.push_back(new Sun(ofVec2f(300, 600), 200, 20000, 500));
}

//--------------------------------------------------------------
void testApp::update() {
    player.update();
    for (int i = 0; i < gravitator.size(); i++) {
        gravitator[i]->update();
    }
    for (int i = 0; i < strandedAstronaut.size(); i++) {
        strandedAstronaut[i]->update();
    }
    for (int i = 0; i < gui.size(); i++) {
        gui[i]->update();
    }

}

//--------------------------------------------------------------
void testApp::draw() {
    for (int i = 0; i < gravitator.size(); i++) {
        gravitator[i]->draw();
    }
    for (int i = 0; i < strandedAstronaut.size(); i++) {
        strandedAstronaut[i]->draw();
    }
    for (int i = 0; i < gui.size(); i++) {
        gui[i]->draw();
    }

    player.draw();

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
    if(clickState == "setting grav") {
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

    ///TOP TEXT DISPLAY-----------------------------------------
    ofSetColor(0, 255, 0);
    string top_text = "";
    top_text.append("level " + ofToString(levelID));
    top_text.append(spacer);
    top_text.append(clickState);
    top_text.append(gap);
    if (clickState == "play mode") {
        top_text.append("[F1] to edit level");
    } else if (clickState == "edit mode") {
        top_text.append(levelState + "\n");
        top_text.append("\n");
        top_text.append("\n");
        top_text.append("[F2] (previous level) || [F3] (next level) || [F5] save level");
    }

    ofDrawBitmapString(top_text, 1, 10);

    if (clickState != "play mode") {
        int draw_x = mouseX + 20;
        int draw_y1 = mouseY + 20;
        int draw_y2 = draw_y1 + 15;

        if (clickState != "edit mode") {
            string mouse_text = "";
            mouse_text.append("placing: ");
            mouse_text.append(new_gravitator_type);
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
        } else placement_text = "";
        ofDrawBitmapString(placement_text, draw_x, draw_y2);

        ///BOTTOM TEXT DISPLAY----------------------------------------
        if (clickState == "edit mode") {
            int x = 50;
            int y = 100;
            string info = "";
            info += "p to place gravitators\n" ;
            info += "s to place player\n";
            info += "shift + c to clear gravitators\n";
            ofDrawBitmapString(info, draw_x, draw_y1);
        }

    }
}

void testApp::addGravitator() {
    if (new_gravitator_type == "planet") {
        gravitator.push_back(new Planet(NEW_PLANET_POS, NEW_PLANET_R, NEW_PLANET_M, NEW_PLANET_GR));
        int chance = ofRandom(3);
        if (chance == 0) {
            addStrandedAstronaut();
        }
    }
    if (new_gravitator_type == "sun") {
        gravitator.push_back(new Sun(NEW_PLANET_POS, NEW_PLANET_R, NEW_PLANET_M, NEW_PLANET_GR));
    }
    if (new_gravitator_type == "black hole") {
        gravitator.push_back(new BlackHole(NEW_PLANET_POS, NEW_PLANET_R, NEW_PLANET_M, NEW_PLANET_GR));
    }
    new_gravitator_type = "";
}

void testApp::addStrandedAstronaut() {
    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(NEW_PLANET_POS.x, NEW_PLANET_POS.y + NEW_PLANET_R), &gravitator, &gui));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    switch (key) {
    case OF_KEY_F1:
        CAN_EDIT_LEVEL = !CAN_EDIT_LEVEL;
        if (clickState == "play mode") {
            clickState = "edit mode";
        } else {
            clickState = "play mode";
        }
        break;
    case 'p':
        if (CAN_EDIT_LEVEL) {
            clickState = "placing gravitators";
            new_gravitator_type = "planet";
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
            importLevel();
        }
        break;
    case OF_KEY_F3:
        if (levelState != "That level doesn't exist.") {
            levelID++;
            importLevel();
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
    case 'z':
        player.rotateDirection(true);
        break;
    case 'x':
        player.rotateDirection(false);
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
        /// TODO (Aaron#2#): Implement ROTATIONAL & ABSOLUTE impulse controls
        /// NOTE (Aaron#5#): Do we need jump *and* ABSOLUTE/ROTATIONAL controls?
        if (player.ON_PLANET) {

            break;
        } else if (player.CAN_JETPACK) {
            player.jetpack();
            break;
        }
    case OF_KEY_DOWN:
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
    case 32:
        player.chargeJump();
        break;
    case '=':
        player.damp += 0.01;
        break;
    case '-':
        player.damp -= 0.01;
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
        break;
    case 32:
        player.jump();
        break;
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
    if (clickState == "placing player") {
        player.pos.set(x, y);
    }

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    if(clickState == "placing gravitators") {
        NEW_PLANET_POS.set(0,0);
        NEW_PLANET_R = 0;
        NEW_PLANET_GR = 0;
        NEW_PLANET_M = 0;
        NEW_PLANET_POS.set(x, y);
        clickState = "setting size";
    }
    if(clickState == "setting grav") {
        if (NEW_PLANET_R < 1) {
            clickState = "edit mode";
            return;
        }
        NEW_PLANET_GR = ofDist(x, y, NEW_PLANET_POS.x, NEW_PLANET_POS.y);
        NEW_PLANET_M = (planet_base_m * NEW_PLANET_R) + (NEW_PLANET_GR * planet_mass_multiplier / NEW_PLANET_R);
        addGravitator();
        clickState = "edit mode";
    }
    if(clickState == "play mode") {

    }
    if(clickState == "placing player") {
        player.pos.set(x, y);
        player.starting_pos.set(player.pos);
        clickState = "play mode";
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
        string levelName = "level_" + ofToString(levelID++);
        std::ifstream input(levelName.c_str());
        if  (!input.good()) {
            std::ofstream output(levelName.c_str());
            output << gravitator.size() << std::endl;
            for (int i = 0; i < gravitator.size(); i++) {
                output << gravitator[i]->pos.x << ' '
                << gravitator[i]->pos.y << ' '
                << gravitator[i]->r << ' '
                << gravitator[i]->m << ' '
                << gravitator[i]->gR << ' '
                << std::endl;
            }
            levelState = "exported as " + ofToString(levelName) + ".";
            break;
        }
    }

}

void testApp::importLevel() {
    std::ifstream input(("level_" + ofToString(levelID)).c_str());
    if (input.good()) {
        gravitator.clear();
        int listSize;
        input >> listSize;
        for(int i = 0; i < listSize; i++) {
            int x, y, r, m, gR;
            input >> x >> y >> r >> m >> gR;
            gravitator.push_back(new Planet(ofVec2f(x, y), r, m, gR));
        }
        levelState = "loaded " + ofToString(levelID) + ".";
    } else {
        levelState = "That level doesn't exist.";
        gravitator.clear();
    }

}
