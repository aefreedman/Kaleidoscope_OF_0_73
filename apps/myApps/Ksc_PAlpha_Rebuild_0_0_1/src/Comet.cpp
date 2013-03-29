#include "Comet.h"

Comet::Comet()
{
    dir.set(0,0);
    currentDest = 0;
    vel = 2;
}

Comet::Comet(ofVec2f _pos, int _r):Gravitator(_pos,_r){

    pos = _pos;
    dir.set(0,0);
    currentDest = 0;
    vel = 2;

    ofVec2f pathStart;
    pathStart.set(pos.x,pos.y);
    pathPoints.push_back(pathStart);

    destination = pathPoints[currentDest];

}

void Comet::update(){

        if (pos.distance(destination) < vel ){
            currentDest +=1;
            if(currentDest > pathPoints.size()-1) currentDest = 0;
            destination = pathPoints[currentDest];
        }

        ofVec2f cometToDestination = destination - pos;
        cometToDestination.normalize();


        dir += .1*cometToDestination;
        dir.normalize();
        pos += dir * vel;

}

void Comet::draw(){

    //draw path with points
    ofPolyline line;
    for (int p=0;p<pathPoints.size();p++){
        ofSetColor(255,255,255);
        ofNoFill();
        ofCircle(pathPoints[p],3);
        line.addVertex(pathPoints[p]);
        ofDrawBitmapString(ofToString(p),pathPoints[p].x+5,pathPoints[p].y+5);
    }
    line.close();
    line.draw();

    //draw comet
    ofFill();
    ofSetColor(255,20,141);
    ofCircle(pos,10);
}

Comet::~Comet()
{

}