#include "MenuScreen.h"
#define dt 1.0/60.0

MenuScreen::MenuScreen() : Screen() {
    //ctor
}

MenuScreen::~MenuScreen() {
    //dtor
}

void MenuScreen::setup() {
    loadResources();
    reset();
}

void MenuScreen::reset() {
    EXPLODING                   = false;
    MOVED                       = false;
    FLASHING                    = false;
    splosionTimer               = 180;
    flashOpacity                = 0;
    flashFadeRate               = 5;

    ///SET START POINTS FOR BROKEN SHIP PIECES! Hoorah.
    piece1.set(329,228,0);
    piece2.set(339,365,0);
    piece3.set(569,400,0);
    piece4.set(550,322,0);
    piece5.set(900,320,0);
    piece6.set(871,440,0);
    piece7.set(307,360,0);

    BROKEN = false;

    anim = ship;
    shipPos.set(400,ofGetHeight()/2);

    splosion.set(shipPos.x,shipPos.y);

    for (int i = 0; i<30; i++) {
        farStars[i].set(ofRandomWidth(),ofRandomHeight(),ofRandom(2,5));
    }
    for (int i = 0; i<30; i++) {
        nearStars[i].set(ofRandomWidth(),ofRandomHeight(),ofRandom(5,8));
    }

    shakeCounter = 4;

    fadeIn.setTimer(3.0);
    fadeIn.setActive(true);
}

void MenuScreen::loadResources() {
    background.loadImage("ART/bg.png");
    title.loadImage("ART/title.png");

    title.setAnchorPoint(title.width/2,title.height/2);
    guiFadeOut = GUIFadeOut(ofVec2f(0, 0));

    font.loadFont("fonts/pixelmix.ttf", 8);

    menuRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 256);
    menuRenderer->loadTexture("ART/ship.png",1024,GL_NEAREST);

    splosionRenderer = new ofxSpriteSheetRenderer(1, 1000, 0, 42);
    splosionRenderer->loadTexture("ART/explosion_sheet.png",462,GL_NEAREST);

    nautRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 64);             /// declare a new renderer with 1 layer, 10000 tiles per layer, default layer of 0, tile size of 32
    nautRenderer->loadTexture("ART/nauts.png", 512, GL_NEAREST);

    ///LOAD SHIP IMAGES
    shipPiece1.loadImage("ART/brokenShip/shipPiece_1.png");
    shipPiece2.loadImage("ART/brokenShip/shipPiece_2.png");
    shipPiece3.loadImage("ART/brokenShip/shipPiece_3.png");
    shipPiece4.loadImage("ART/brokenShip/shipPiece_4.png");
    shipPiece5.loadImage("ART/brokenShip/shipPiece_5.png");
    shipPiece6.loadImage("ART/brokenShip/shipPiece_6.png");
    shipPiece7.loadImage("ART/brokenShip/shipPiece_7.png");

    if (LOAD_WITH_SOUND) {
        fxEngineLoop.loadSound("AUDIO/ksc_AUDIO_ship_engineloop_001.wav");
        fxEngineLoop.setLoop(true);
        fxEngineLoop.play();

        fxSmallExplosion.loadSound("AUDIO/ksc_AUDIO_ship_explosion_003.wav");
        fxSmallExplosion.setMultiPlay(true);

        fxExplosion.loadSound("AUDIO/ksc_AUDIO_ship_explosion_002.wav");
        fxExplosion.setSpeed(0.5);

        fxEngineAmbient.loadSound("AUDIO/ksc_AUDIO_ship_engineambient_001.wav");
        fxEngineAmbient.setLoop(true);
        fxEngineAmbient.play();
    }
}

void MenuScreen::update() {
    menuRenderer->clear();
    splosionRenderer->clear();
    menuRenderer->addCenteredTile(&anim,shipPos.x,shipPos.y,-1,F_NONE,5,255,255,255,255);
    menuRenderer->update(ofGetElapsedTimeMillis());

    if (EXPLODING) {
        if(explosion.frame == 11) {
            splosion.set(shipPos.x + ofRandom(-200,300), shipPos.y + ofRandom(-200,200));
            fxSmallExplosion.setSpeed(ofRandom(0.9, 1.0));
            fxSmallExplosion.play();
        }

        splosionRenderer->addCenteredTile(&explosion, splosion.x, splosion.y, -1, F_NONE,5,255,255,255,255);
        splosionRenderer->update(ofGetElapsedTimeMillis());

        if (splosionTimer > 0) {
            splosionTimer --;
        } else {
            FLASHING = true;
        }
    }

    if (FLASHING) {
        //if (flashOpacity >= 255) {
            //EXPLODING       = false;
            //BROKEN          = true;
            //fxExplosion.play();
            //fxEngineAmbient.stop();
            //fxEngineLoop.stop();
            //flashFadeRate   = -5;
        //}
        flashOpacity += flashFadeRate;
    }

    if (shakeCounter > 0) {
        shakeCounter --;
    } else {
        shipPos.set(ofRandom(395,405),ofRandom((ofGetHeight()/2)-5,(ofGetHeight()/2)+5));
        shakeCounter = 2;
    }

    for(int i = 0; i<30; i++) {
        farStars[i].x-=15*(farStars[i].z/5);
        nearStars[i].x-=30*(nearStars[i].z/8);
        if(farStars[i].x < 0) {
            farStars[i].x = ofGetWidth();
            farStars[i].y = ofRandomHeight();
        }
        if(nearStars[i].x < 0) {
            nearStars[i].x = ofGetWidth();
            nearStars[i].y = ofRandomHeight();
        }
    }
    guiFadeOut.update();

    /// LET'S ROTATE THE FLOATING PIECES YOU IDIOT
    if(BROKEN) {
        if (!guiFadeOut.getActive())
            guiFadeOut.setActive(true);
        piece1.x += -.1;
        piece1.y += -.05;
        piece1.z += .1;

        piece2.x += -1;
        piece2.y += .5;
        piece2.z += -1;

        piece3.x += .2;
        piece3.y += 1;
        piece3.z += -1;

        piece4.x += -.1;
        piece4.y += -2;
        piece4.z += .3;

        piece5.x += 2;
        piece5.y += -.2;
        piece5.z += -.4;

        piece6.x += 0;
        piece6.y += 0;
        piece6.z += 1;

        piece7.x += -2;
        piece7.y += .2;
        piece7.z += 2;

        /// SHOULD THIS ACTIVATE THE NEXT LEVEL??? I DON'T KNOW???
    }
}

void MenuScreen::draw() {
    ofSetColor(255,255,255);
    background.draw(0,0);

    for (int i = 0; i < 30; i++) {
        ofSetColor(255,255,255,180*(farStars[i].z/5));
        ofRect(farStars[i].x,farStars[i].y,farStars[i].z,farStars[i].z);
    }
    for (int i = 0; i < 30; i++) {
        ofSetColor(255,255,255,155*(farStars[i].z/8));
        ofRect(nearStars[i].x,nearStars[i].y,nearStars[i].z*(10*(nearStars[i].z/8)),nearStars[i].z/(2*(nearStars[i].z/8)));
    }
    ofSetColor(255,255,255,255);
    title.draw(ofGetWidth()/2,100);

    if (!BROKEN) {
        menuRenderer->draw();
    } else {
        ofPushMatrix();
        ofTranslate(piece5.x,piece5.y,0);
        ofRotateZ(piece5.z);
        shipPiece5.draw(0,0);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(piece3.x,piece3.y,0);
        ofRotateZ(piece3.z);
        shipPiece3.draw(0,0);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(piece4.x,piece4.y,0);
        ofRotateZ(piece4.z);
        shipPiece4.draw(0,0);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(piece6.x,piece6.y,0);
        ofRotateZ(piece6.z);
        shipPiece6.draw(0,0);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(piece7.x,piece7.y,0);
        ofRotateZ(piece7.z);
        shipPiece7.draw(0,0);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(piece2.x,piece2.y,0);
        ofRotateZ(piece2.z);
        shipPiece2.draw(0,0);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(piece1.x,piece1.y,0);
        ofRotateZ(piece1.z);
        shipPiece1.draw(0,0);
        ofPopMatrix();


    }

    splosionRenderer->draw();

    ofDrawBitmapString("- SPACE TO START -", ofGetWidth()/2 - 75, ofGetHeight() - 75);

    if (FLASHING == true) {
        ofSetColor(255,255,255, flashOpacity);
        ofFill();
        ofRect(0,0,1280,720);
    }

    guiFadeOut.draw();

    font.drawString("Created by: \n     Aaron Freedman\n     Diego Garcia\n     Toni Pizza", 20, ofGetHeight() - 50);
}


//--------------------------------------------------------------
void MenuScreen::keyPressed(int key) {

}

//--------------------------------------------------------------
void MenuScreen::keyReleased(int key) {

}

//--------------------------------------------------------------
void MenuScreen::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void MenuScreen::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void MenuScreen::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void MenuScreen::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void MenuScreen::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void MenuScreen::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void MenuScreen::dragEvent(ofDragInfo dragInfo) {

}

