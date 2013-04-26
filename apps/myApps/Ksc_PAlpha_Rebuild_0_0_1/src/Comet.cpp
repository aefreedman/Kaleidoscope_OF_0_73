#include "Comet.h"
#define dt 1.0/60.0

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
    vel                         = 1.5;
    m                           = 0.0;
    gR                          = 0;
    r                           = 20;
    type                        = "comet";
    anim                        = comet;
    spawnTimer_init             = 0.001;                /// This needs to be a multiple of 0.0166r
    spawnTimer                  = spawnTimer_init;
    particle_max_size           = 5.0;
    particle_min_size           = 1.0;
    particle_pos_range          = 18.0;
    particle_fade_rate          = 2.0 / dt;
    particle_v                  = -vel / 4;
    particles_per_frame         = 15;
    cometColor.r                = 169;
    cometColor.g                = 241;
    cometColor.b                = 231;
    cometColor_a_min            = 150;
    cometColor_a_max            = 255;

    perpDir = dir.getPerpendicular();
    tail1.set(pos.x + 20*dir.x,pos.y+20*dir.y);
    tail2.set(pos.x + 20*perpDir.x, pos.y + 20*perpDir.y);
    tail8.set(pos.x - 20*perpDir.x,pos.y - 20*perpDir.y);

    for (int i = 0; i < 50; i++){
        posArray[i] = pos;
    }

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
        spawnTimer -= dt;
    } else {
        for (int i = 0; i < particles_per_frame; i++) {
            spawnParticle();
        }
        spawnTimer = spawnTimer_init;
    }
    if (ptclColor.size() > 1){
        for (int i = 0;i<ptclColor.size();){
            ptclPosSize[i].x += ptclDir[i].x;
            ptclPosSize[i].y += ptclDir[i].y;
            ptclPosSize[i].z -= particle_fade_rate;
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
    if (ptclColor.size() > 1){
        for (int i = 0;i<ptclColor.size();i++){
            ofSetColor(ptclColor[i]);
            ofFill();
            ofRect(ptclPosSize[i].x,ptclPosSize[i].y,ptclPosSize[i].z,ptclPosSize[i].z);
        }
    }
}

void Comet::drawPath() {
    ofPolyline line;
    for (int p = 1; p < pathPoints.size(); p++) {
        ofSetColor(255, 255, 255);
        ofNoFill();
        ofCircle(pathPoints[p], 3);
        line.addVertex(pathPoints[p]);
        ofDrawBitmapString(ofToString(p), pathPoints[p].x + 5, pathPoints[p].y + 5);
    }
    line.close();
    line.draw();
}

void Comet::spawnParticle() {
    cometColor.a = ofRandom(cometColor_a_min, cometColor_a_max);
    ofVec3f newPos;
    newPos.set(ofVec3f(ofRandom(pos.x - particle_pos_range, pos.x + particle_pos_range), ofRandom(pos.y - particle_pos_range, pos.y + particle_pos_range), ofRandom(particle_min_size , particle_max_size)));
    newPos.z*=(r-(ofDist(pos.x,pos.y,newPos.x,newPos.y)/r))/r;
    ptclPosSize.push_back(newPos);
    ptclColor.push_back(cometColor);
    ptclDir.push_back(dir * particle_v);
}

Comet::~Comet() {

}
