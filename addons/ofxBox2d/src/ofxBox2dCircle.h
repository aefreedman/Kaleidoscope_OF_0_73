
#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"

class ofxBox2dCircle : public ofxBox2dBaseShape {

private:

    float radius;

public:

    //------------------------------------------------
    ofxBox2dCircle();

    //------------------------------------------------
    void setup(b2World * b2dworld, float x, float y, float radius, float lDamping, float aDamping);
    void setup(b2World * b2dworld, ofVec2f &pts, float radius, float lDamping, float aDamping);

    //------------------------------------------------
    float getRadius();
    void  setRadius(float r);

    //------------------------------------------------
    virtual void draw();

    //------------------------------------------------
    void addAttractionPoint(float x, float y, float amt=1);
    void addAttractionPoint(ofVec2f pt, float amt=1);

    void addRepulsionForce(float x, float y, float amt);
    void addRepulsionForce(ofVec2f pt, float amt);
    void addImpulseForce(ofVec2f pt, ofVec2f amt);

    void increaseGravity(float amt);

};














