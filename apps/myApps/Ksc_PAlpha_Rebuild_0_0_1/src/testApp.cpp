#include "testApp.h"
#include <fstream>
#define nl '\n'
#define screen_width 1280
#define screen_height 720
#define dt 1.0/60.0

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);

    player                          = Player(ofVec2f(300,300), &gravitator, &strandedAstronaut);
    clickState                      = "play mode";
    levelState                      = "Working from scratch.";
    planet_base_m                   = 1000;
    planet_mass_multiplier          = 250;

    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(screen_width / 2, screen_height / 2), &gravitator));
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
}

//--------------------------------------------------------------
void testApp::draw() {
    for (int i = 0; i < gravitator.size(); i++) {
        gravitator[i]->draw();
    }
    for (int i = 0; i < strandedAstronaut.size(); i++) {
        strandedAstronaut[i]->draw();
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
    ofDrawBitmapString("level " + ofToString(levelID), ofGetWidth()/2, 20);
    ofDrawBitmapString("W (level++), Q (level--), E to export, I to import.", ofGetWidth()/2 - 300, 50);
    ofDrawBitmapString(levelState, ofGetWidth()/2, 35);
    ofDrawBitmapString(clickState, 40,65);
    if (clickState == "placing gravitators") {
        ofDrawBitmapString("click & hold to place origin, release to set size.",40,80);
    } else if (clickState == "setting size") {
        ofDrawBitmapString("release to set size.",40,80);
    } else if (clickState == "setting grav") {
        ofDrawBitmapString("click to set gravity range.", 40,80);
    } else if (clickState == "placing player") {
        ofDrawBitmapString("click to set player location", 40,80);
    }

    ///BOTTOM TEXT DISPLAY----------------------------------------
    int x = 50;
    int y = 100;
    string info = "";
    info += "p to place gravitators\n" ;
    info += "s to place player\n";
    info += "shift + c to clear gravitators\n";
    ofDrawBitmapString(info, x, y);
}

void testApp::addGravitator() {
    gravitator.push_back(new Planet(NEW_PLANET_POS, NEW_PLANET_R, NEW_PLANET_M, NEW_PLANET_GR));
    int chance = ofRandom(3);
    if (chance == 0) {
        addStrandedAstronaut();
    }
}

void testApp::addStrandedAstronaut() {
    strandedAstronaut.push_back(new StrandedAstronaut(ofVec2f(NEW_PLANET_POS.x, NEW_PLANET_POS.y + NEW_PLANET_R), &gravitator));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    switch (key) {
    case 'g':
        player.USING_GRAVITY = !player.USING_GRAVITY;
        break;
    case 'G':
        player.SIMPLE_GRAVITY = !player.SIMPLE_GRAVITY;
        break;
    case 'p':
        clickState = "placing gravitators";
        break;
    case 's':
        clickState = "placing player";
        player.setup();
        break;
    case 'w':
        clickState = "placing walls";
        break;
    case 'E':
        exportLevel();
        break;
    case 'I':
        importLevel();
        break;
    case 'Q':
        levelID--;
        break;
    case 'W':
        levelID++;
        break;
    case 'C':
        gravitator.clear();
        break;
    case 'z':
        player.rotateDirection(true);
        break;
    case 'x':
        player.rotateDirection(false);
        break;
    case OF_KEY_UP:
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
        if (!player.CAN_LAND_ON_PLANET) {
            player.traversePlanet(true);
            break;
        } else {
            player.rotateDirection(true);
            break;
        }
    case OF_KEY_RIGHT:
        if (!player.CAN_LAND_ON_PLANET) {
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
        NEW_PLANET_GR = ofDist(x, y, NEW_PLANET_POS.x, NEW_PLANET_POS.y);
        NEW_PLANET_M = (planet_base_m * NEW_PLANET_R) + (NEW_PLANET_GR * planet_mass_multiplier / NEW_PLANET_R);
        addGravitator();
        clickState = "play mode";
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
    }

}
