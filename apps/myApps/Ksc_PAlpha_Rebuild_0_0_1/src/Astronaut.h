#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include <vector>
#include <iostream>
#include "ofMain.h"
#include "Gravitator.h"

class Astronaut {
public:
    Astronaut();
    Astronaut(ofVec2f _pos);
    //Astronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator);
    virtual ~Astronaut();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void move() = 0;

    void detectPlanetcollisions();
    void collisionData(int collision);
    void bounce();
    void calculateGravity(int attractor);

    std::vector<Gravitator *> *gravitator;


    ofVec2f pos;
    ofVec2f starting_pos;
    ofVec2f gravity;
    ofVec2f v;
    ofVec2f a;
    ofVec2f p;
    ofVec2f jp;
    ofVec2f left;
    ofVec2f right;
    ofVec2f jumpDir;
    ofVec2f f;
    ofVec2f dir;
    ofVec2f angular_v;
    ofQuaternion orientation;

    float m;
    float rotation;
    float damp;
    float restitution;
    float oxygen;

    int w;
    int h;
    int r;
    int collision;
    int attractor;
protected:
private:


};

#endif // ASTRONAUT_H
