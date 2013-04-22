#include "MenuScreen.h"

MenuScreen::MenuScreen() : Screen() {
    //ctor
}

MenuScreen::~MenuScreen() {
    //dtor
}

void MenuScreen::setup() {

    ofSetFrameRate(60);
    background.loadImage("ART/bg.png");
    title.loadImage("ART/title.png");
    title.setAnchorPoint(title.width/2,title.height/2);
    menuRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 256);
    menuRenderer->loadTexture("ART/ship.png",1024,GL_NEAREST);
    anim = ship;
    shipPos.set(400,ofGetHeight()/2);

    for (int i = 0; i<30; i++){
        farStars[i].set(ofRandomWidth(),ofRandomHeight(),ofRandom(2,5));
    }
    for (int i = 0; i<30;i++){
        nearStars[i].set(ofRandomWidth(),ofRandomHeight(),ofRandom(5,8));
    }

    shakeCounter = 4;

    fxEngineLoop.loadSound("AUDIO/ksc_AUDIO_ship_engineloop_001.wav");
    fxEngineLoop.setLoop(true);
    fxEngineLoop.play();

    fxExplosion.loadSound("AUDIO/ksc_AUDIO_ship_explosion_001.wav");
    fxExplosion.setSpeed(0.5);

    guiFadeOut = GUIFadeOut(ofVec2f(0, 0));

}

void MenuScreen::update() {
    menuRenderer->clear();
    menuRenderer->addCenteredTile(&anim,shipPos.x,shipPos.y,-1,F_NONE,5,255,255,255,255);
    menuRenderer->update(ofGetElapsedTimeMillis());

    if (shakeCounter > 0){
    shakeCounter --;
    } else {
        shipPos.set(ofRandom(395,405),ofRandom((ofGetHeight()/2)-5,(ofGetHeight()/2)+5));
        shakeCounter = 2;
    }



    for(int i = 0;i<30;i++){
        farStars[i].x-=15*(farStars[i].z/5);
        nearStars[i].x-=30*(nearStars[i].z/8);
        if(farStars[i].x < 0){
            farStars[i].x = ofGetWidth();
            farStars[i].y = ofRandomHeight();
        }
        if(nearStars[i].x < 0){
            nearStars[i].x = ofGetWidth();
            nearStars[i].y = ofRandomHeight();
        }
    }
    guiFadeOut.update();
}

void MenuScreen::draw() {
    ofSetColor(255,255,255);
    background.draw(0,0);

    for (int i = 0; i < 30; i++){
        ofSetColor(255,255,255,180*(farStars[i].z/5));
        ofRect(farStars[i].x,farStars[i].y,farStars[i].z,farStars[i].z);
    }
    for (int i = 0; i < 30; i++){
        ofSetColor(255,255,255,155*(farStars[i].z/8));
        ofRect(nearStars[i].x,nearStars[i].y,nearStars[i].z*(10*(nearStars[i].z/8)),nearStars[i].z/(2*(nearStars[i].z/8)));
    }
    ofSetColor(255,255,255,255);
    title.draw(ofGetWidth()/2,100);

    menuRenderer->draw();

    ofDrawBitmapString("- SPACE TO START -", ofGetWidth()/2-75,ofGetHeight()-75);
    guiFadeOut.draw();
}


//--------------------------------------------------------------
void MenuScreen::keyPressed(int key){
    switch (key) {
        case 32:
            guiFadeOut.ACTIVE = true;
        break;
    }

}

//--------------------------------------------------------------
void MenuScreen::keyReleased(int key){

}

//--------------------------------------------------------------
void MenuScreen::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void MenuScreen::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void MenuScreen::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void MenuScreen::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void MenuScreen::windowResized(int w, int h){

}

//--------------------------------------------------------------
void MenuScreen::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MenuScreen::dragEvent(ofDragInfo dragInfo){

}

