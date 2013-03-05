#include <fstream>

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

    ofBackground(0,0,0);
    ofSetFrameRate(60);
    ofSetCircleResolution(30);

    clickState = "play mode";
    levelState = "Working from scratch.";

    planetHabitability = true;

    //ship = Ship(0,0);
    player = Player(0,0);

}

//--------------------------------------------------------------
void testApp::update() {

    //ship.update();

    for (int i=0; i<walls.size(); i++) {
        walls[i].update();

        if(player.location.x > walls[i].location.x && player.location.x < walls[i].location.x + walls[i].width && player.location.y > walls[i].location.y && player.location.y < walls[i].location.y+walls[i].height) {
            player.location = player.location - player.momentum;
            player.momentum.set(0,0);

        }
    }

    player.nearPlanet = false;


    player.update();

    for (int i=0; i<planets.size(); i++) {
        planets[i].update();
        if(pointDist(planets[i].location,player.location)<planets[i].gravRange) {
            player.adjustDirPlanet(planets[i].location, planets[i].size, planets[i].habitable);
            player.nearPlanet = true;
        }
    }


}

//--------------------------------------------------------------
void testApp::draw() {

    //ship.draw();


    if (clickState == "setting size") {
        ofSetColor(0,255,0);
        ofNoFill();
        ofCircle(planetPoint,ofDist(mouseX,mouseY,planetPoint.x,planetPoint.y));
    }
    if(clickState == "setting grav") {
        ofSetColor(0,255,0);
        ofNoFill();
        ofCircle(planetPoint,ofDist(mouseX,mouseY,planetPoint.x,planetPoint.y));
        ofSetColor(230,230,255);
        ofNoFill();
        ofCircle(planetPoint,planetSize);

        ofSetColor(0,255,0);
        ofDrawBitmapString("press 'h' to toggle habitability. (right now it's " + ofToString(planetHabitability) + ".)", 40,100);
    }
    if(clickState == "placing walls") {
        ofSetColor(0,255,0);
        ofNoFill();
        ofRect(wallPoint,wallWidth,wallHeight);

    }

    for (int i=0; i<planets.size(); i++) {
        planets[i].draw();
    }
    for (int i=0; i<walls.size(); i++) {
        walls[i].draw();
    }

    player.draw();

    //TOP TEXT DISPLAY
    ofSetColor(0,255,0);
    ofDrawBitmapString("level " + ofToString(levelID), ofGetWidth()/2, 20);
    ofDrawBitmapString("shift + w to advance level ID, shift + q to go back. shift + e to export, shift + i to import.", ofGetWidth()/2 - 300, 50);
    ofDrawBitmapString(levelState, ofGetWidth()/2, 35);
    ofDrawBitmapString(clickState, 40,65);
    if (clickState == "placing planets") {
        ofDrawBitmapString("click & hold to place origin, release to set size.",40,80);
    } else if (clickState == "setting size") {
        ofDrawBitmapString("release to set size.",40,80);
    } else if (clickState == "setting grav") {
        ofDrawBitmapString("click to set gravity range.", 40,80);
    } else if (clickState == "placing player") {
        ofDrawBitmapString("click to set player location", 40,80);
    }
    ofDrawBitmapString("dir is " + ofToString(player.dir),40,95);
    ofDrawBitmapString("max jump is " + ofToString(player.maxJump),40,110);

    //BOTTOM TEXT DISPLAY
    ofDrawBitmapString("p to place planets.", 600,685);
    ofDrawBitmapString("w to place walls.", 600,700);
    ofDrawBitmapString("s to place player.", 600,715);
    ofDrawBitmapString("shift + c to clear planets.", 600,730);
    ofDrawBitmapString("1 key lowers max jump strength. 2 key raises.", 600,745);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    cout << "pressed " + ofToString(key) + " and then ";

    switch (key) {
        //p
    case 'p':
        clickState = "placing planets";
        break;
        //s
    case 's':
        clickState = "placing player";
        player.momentum.set(0,0);
        player.dir.set(0,0);
        break;
    case 'w':
        clickState = "placing walls";
        break;
    case OF_KEY_LEFT:
        player.dir.set(player.leftDir);
        break;
        //right
    case OF_KEY_RIGHT:
        player.dir.set(player.rightDir);
        break;
    case 32:
        player.chargeJump();
        break;
    case 'C':
        planets.clear();
        break;
    case '1':
        player.maxJump -= 1;
        break;
    case '2':
        player.maxJump+=1;
        break;
    case 'h':
        if (clickState == "setting grav") {
            planetHabitability = !planetHabitability;
        }
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
    }
}


void testApp::addPlanet(ofPoint _location, int _size, int _gravRange) {
    Planet planet;
    planet.location.set(_location.x,_location.y);
    planet.size = _size;
    planet.gravRange = _gravRange;
    planet.habitable = planetHabitability;
    planets.push_back(planet);
}

// --  get distance b/w two points --
float testApp::pointDist(ofPoint _p1, ofPoint _p2) {
    return ofDist(_p1.x,_p1.y,_p2.x,_p2.y);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

    switch (key) {
    case 356:
        if (ofGetKeyPressed(358)) {
            player.dir.set(player.rightDir);
        } else {
            player.dir.set(0,0);
        }
        break;
    case 358:
        if (ofGetKeyPressed(356)) {
            player.dir.set(player.leftDir);
        } else {
            player.dir.set(0,0);
        }
        break;
    case 32:
        player.jump();
        break;

    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

    //ship.location.set(x,y);
    if (clickState == "placing player") {
        player.location.set(x,y);
    }

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

    if(clickState == "placing planets") {
        planetPoint.set(0,0);
        planetSize = 0;
        planetGrav = 0;
        planetPoint.set(x,y);
        clickState = "setting size";
    }
    if(clickState == "setting grav") {
        planetGrav = ofDist(x,y,planetPoint.x,planetPoint.y);
        addPlanet(planetPoint,planetSize,planetGrav);
        clickState = "play mode";
    }
    if(clickState == "play mode") {

    }
    if(clickState == "placing player") {
        player.location.set(x,y);
        clickState = "play mode";
    }
    if(clickState == "placing walls") {
        wallPoint.set(x,y);
        clickState = "setting wall size";
    }

}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

    if (clickState == "setting size") {
        planetSize = ofDist(x,y,planetPoint.x,planetPoint.y);
        clickState = "setting grav";
    }
    if (clickState == "setting wall size") {
        wallHeight = y - wallPoint.y;
        wallWidth = x - wallPoint.x;
        addWall(wallPoint,wallWidth,wallHeight);
        clickState = "play mode";
    }

}

void testApp::addWall(ofPoint _location, int _width, int _height) {
    Wall wall;
    wall.location.set(_location.x,_location.y);
    wall.width = _width;
    wall.height = _height;
    walls.push_back(wall);
}

void testApp::exportLevel() {





    while (true) {
        string levelName = "level_" + ofToString(levelID++);
        std::ifstream input(levelName.c_str());
        if  (!input.good()) {
            std::ofstream output(levelName.c_str());
            output << planets.size() << std::endl;
            for (int i = 0; i<planets.size(); i++) {
                output << planets[i].location.x << ' '
                << planets[i].location.y << ' '
                << planets[i].size << ' '
                << planets[i].gravRange << ' '
                << planets[i].habitable << std::endl;
            }
            levelState = "exported as " + ofToString(levelName) + ".";
            break;
        }


    }

}

void testApp::importLevel() {

    std::ifstream input(("level_" + ofToString(levelID)).c_str());
    if (input.good()) {
        planets.clear();
        int listSize;
        input >> listSize;
        for(int i = 0; i < listSize; i++) {
            int x, y, size, gravRange;
            bool habitable;
            input >> x >> y >> size >> gravRange >> habitable;
            Planet planet(x,y,size,gravRange,habitable);
            planets.push_back(planet);
        }
        levelState = "loaded " + ofToString(levelID) + ".";
    } else {
        levelState = "That level doesn't exist.";
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
