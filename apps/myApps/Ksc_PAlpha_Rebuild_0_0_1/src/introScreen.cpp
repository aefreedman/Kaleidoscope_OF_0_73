#include "IntroScreen.h"


IntroScreen::IntroScreen()
{
    //ctor
    setup();
}

IntroScreen::~IntroScreen()
{
    //dtor
}

void IntroScreen::setup(){

    ofBackground(0,0,0);

    currentFrame = 0;

    FADING_IN = true;
    fadeOpacity = 255;

    FADING_OUT = false;
    fadeOutOpacity = 0;

    framePos.set(ofGetWidth()/2,211);
    capSpeech = "";
    capSpeechPos.set(400,140);
    nautSpeech = "";
    nautSpeechPos.set(350,70);

    nautFont.loadFont("fonts/pixelmix.ttf",8);
    capFont.loadFont("fonts/pixelmix.ttf",12);

    anim = shipExplode;

    introRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 322);
    introRenderer->loadTexture("ART/introSheet.png",3542,GL_NEAREST);

}

void IntroScreen::update(){

    introRenderer->clear();

    introRenderer->addCenteredTile(&anim,framePos.x,framePos.y,-1,F_NONE,2,255,255,255,255);

    introRenderer->update(ofGetElapsedTimeMillis());

        if (fadeOpacity <= 0){
            FADING_IN = false;
        }

    if (currentFrame >= 17 && anim.frame >= 3){
        FADING_OUT = true;
    }

}

void IntroScreen::draw(){

    introRenderer->draw();

        if (anim.index == capSpeaks.index && anim.frame == 3){
        ofSetColor(255,255,255);
        capFont.drawString(capSpeech,capSpeechPos.x,capSpeechPos.y);
        } else if (anim.index == nautSpeaks.index || anim.index == nautSpeaks2.index){
            if(anim.frame == 3){
                ofSetColor(255,255,255);
                nautFont.drawString(nautSpeech,nautSpeechPos.x,nautSpeechPos.y);
            }
        }

        if (FADING_IN){
            ofSetColor(255,255,255,fadeOpacity);
            ofRect(0,0,ofGetWidth(),ofGetHeight());
            fadeOpacity -= 5;
        } else if (FADING_OUT){
            ofSetColor(0,0,0,fadeOutOpacity);
            ofRect(0,0,ofGetWidth(),ofGetHeight());
            fadeOutOpacity += 5;
        }


}

void IntroScreen::keyPressed(int key){
    if (key == ' '){
        currentFrame += 1;
    }

        switch (currentFrame){
        case 0:
            anim = shipExplode;
            break;
        case 1:
            anim = captainFlies;
            break;
        case 2:
            anim = noSpeech;
            break;
        case 3:
            anim = nautSpeaks;
            nautSpeech = "Captain! \nCome in!";
            break;
        case 4:
            anim = nautsDone;
            break;
        case 5:
            anim = nautSpeaks;
            nautSpeech = "Captain! \nCan you \nhear me!?";
            break;
        case 6:
            anim = nautsDone;
            break;
        case 7:
            anim = capSpeaks;
            capSpeech = "...Y-yes, I hear you.";
            break;
        case 8:
            anim = capsDone;
            break;
        case 9:
            anim = nautSpeaks2;
            nautSpeech = "Captain! The"
            "\nship's torn"
            "\nto bits! We"
            "\nhave no way"
            "\nto get home!"
            "\nWe're gonna"
            "\ndie alone"
            "\nout here!";
            break;
        case 10:
            anim = nautsDone2;
            break;
        case 11:
            anim = capSpeaks;
            capSpeech = "...";
            break;
        case 12:
            anim = capsDone;
            break;
        case 13:
            anim = capSpeaks;
            capSpeech = "You're right.\n";
            capSpeech += "We're going to die.";
            break;
        case 14:
            anim = capsDone;
            break;
        case 15:
            anim = capSpeaks;
            capSpeech = "But we're not\n"
            "going to die \n"
            "alone."
            "\nI won't let"
            "\nthat happen.";
            break;
        case 16:
            anim = capsDone;
            break;
        case 17:
            anim = flyOff;
            break;
    }


}
