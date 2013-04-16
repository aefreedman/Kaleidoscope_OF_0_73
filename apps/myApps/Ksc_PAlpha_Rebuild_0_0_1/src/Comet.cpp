#include "Comet.h"

Comet::Comet() : Gravitator() {
    setup();
}

Comet::Comet(ofVec2f _pos, int _r) : Gravitator(_pos, _r) {
    setup();
    pos                         = _pos;
    destination                 = pathPoints[currentDest];
    type                        = "comet";
    pos                         = pathPoints[0];


}

Comet::Comet(ofVec2f _pos, int _r, vector <ofVec2f> _pathPoints) : Gravitator(_pos, _r) {
    setup();
    pos                         = _pos;
    pathPoints                  = _pathPoints;
    destination                 = pathPoints[currentDest];
    pos                         = pathPoints[0];


}

void Comet::setup(){

    dir.set(0,0);
    currentDest                 = 0;
    vel                         = 2;
    m                           = 0.0;
    gR                          = 0;
    type                        = "comet";
    anim                        = comet;
    spawnTimer                  = 2;

}

void Comet::update() {

    if (pos.distance(destination) < vel ) {
        currentDest +=1;
        if(currentDest > pathPoints.size()-1) currentDest = 0;
        destination = pathPoints[currentDest];
    }

    ofVec2f cometToDestination = destination - pos;
    cometToDestination.normalize();


    dir += .1*cometToDestination;
    dir.normalize();
    pos += dir * vel;

    if (spawnTimer > 0){
        spawnTimer --;
    } else {
        spawnParticle();
        spawnTimer = 2;
    }
    if (ptclColor.size() > 1){
        for (int i = 0;i<ptclColor.size();){
            ptclPosSize[i].x += ptclDir[i].x;
            ptclPosSize[i].y += ptclDir[i].y;
            ptclPosSize[i].z -=.1;
            if (ptclPosSize[i].z < 0){
                ptclPosSize.erase(ptclPosSize.begin()+i);
                ptclColor.erase(ptclColor.begin()+i);
                ptclDir.erase(ptclDir.begin()+i);
            } else {
                i++;
            }
        }
    }

}

void Comet::draw() {

    ///draw path with points
    ofPolyline line;
    for (int p = 1; p < pathPoints.size(); p++) {
        //ofSetColor(255, 255, 255);
        //ofNoFill();
        //ofCircle(pathPoints[p], 3);
        line.addVertex(pathPoints[p]);
        //ofDrawBitmapString(ofToString(p), pathPoints[p].x + 5, pathPoints[p].y + 5);
    }
    line.close();
   // line.draw();
    ///draw comet
    /*ofFill();
    ofSetColor(255,20,141);
    ofCircle(pos,10);*/

    if (ptclColor.size() > 1){
        for (int i = 0;i<ptclColor.size();i++){
            ofSetColor(ptclColor[i]);
            ofFill();
            ofRect(ptclPosSize[i].x,ptclPosSize[i].y,ptclPosSize[i].z,ptclPosSize[i].z);
        }
    }
}

void Comet::spawnParticle() {
    ptclPosSize.push_back(ofVec3f(ofRandom(pos.x-20,pos.x+20),ofRandom(pos.y-20,pos.y+20),ofRandom(4,10)));
    ptclColor.push_back(ofColor(169,241,231,ofRandom(150,255)));
    ptclDir.push_back(dir * .5);
}

Comet::~Comet() {

}
