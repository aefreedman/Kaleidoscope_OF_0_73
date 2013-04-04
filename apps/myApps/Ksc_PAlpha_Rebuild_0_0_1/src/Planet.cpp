#include "Planet.h"

Planet::Planet() : Gravitator() {}

Planet::Planet(ofVec2f _pos, int _r, int _m, int _gR) : Gravitator(_pos, _r, _m, _gR) {
    habitable = true;
    type = "planet";

    planetRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 120); //declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
	planetRenderer->loadTexture("rockPlanet.png", 120, GL_NEAREST); // load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    anim = planet1;

	ofEnableAlphaBlending(); // turn on alpha blending. important!
}

Planet::Planet(ofVec2f _pos, int _r, int _gR) : Gravitator(_pos, _r, _gR) {
    habitable = true;
    type = "planet";

    planetRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 120); //declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
	planetRenderer->loadTexture("rockPlanet.png", 120, GL_NEAREST); // load the spriteSheetExample.png texture of size 256x256 into the sprite sheet. set it's scale mode to nearest since it's pixel art

    anim = planet1;

    ofEnableAlphaBlending(); // turn on alpha blending. important!
}

Planet::~Planet() {
    //dtor
}

void Planet::setup() {

}

void Planet::update() {

    planetRenderer->clear(); // clear the sheet
	planetRenderer->update(ofGetElapsedTimeMillis());

	planetRenderer->addCenteredTile(&anim, pos.x, pos.y, -1, F_NONE, 2.0*r/120.0, 255, 255, 255, 255);

}

void Planet::draw() {
   /* ofSetCircleResolution(64);
    ofFill();
    ofSetColor(255, 255, 255, 255);
    ofCircle(pos, r);*/

    planetRenderer -> draw();

    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    ofCircle(pos, gR);

    ofSetColor(255, 0, 0, 255);
    ofDrawBitmapString(ofToString(m), pos);

}

