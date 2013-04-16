#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include <vector>
#include <iostream>
#include "ofMain.h"
#include "Gravitator.h"
#include "GUI.h"
#include "GUIOverlay.h"
#include "Message.h"
#include "ofxSpriteSheetRenderer.h"


class Astronaut {
public:
    Astronaut();
    Astronaut(ofVec2f _pos);
    Astronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator);
    virtual ~Astronaut();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void move() = 0;
/// TODO (Aaron#1#): Astronaut gravity and movement can be moved to Astronaut, but needs to handle the Gravitator vector first.
/// TODO (Aaron#1#): Different collision conditions for objects
    virtual void detectGravitatorCollisions();

    virtual void collisionData(int collision);
    virtual void orientToPlanet(int collision);
    void gravitatorBounce();
    virtual void calculateGravity(int attractor);

    virtual void checkState();

    virtual void drawGUIOverlay(ofVec2f _pos, string text);
    virtual void displayMessage(ofVec2f _pos, string text);

    std::vector<Gravitator *> *gravitator;
    std::vector<GUI *> *gui;

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

    bool HIT_GRAVITATOR;
    bool IN_GRAVITY_WELL;
    bool EXITED_GRAVITY_WELL;
    bool ORIENT_TO_PLANET;
    bool USING_GRAVITY;
    bool SIMPLE_GRAVITY;
    //bool CAN_LAND_ON_PLANET;
    //bool TRAVERSING_PLANET;

    float G;
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

    animation_t anim;

protected:

    ofVec2f planet_pos;
    ofVec2f collision_normal;
    ofVec2f normalized_collision_normal;
    ofVec2f collision_perpendicular;
    float planet_m;
    float planet_r;
    string gravitator_type;
private:



};

#endif // ASTRONAUT_H
