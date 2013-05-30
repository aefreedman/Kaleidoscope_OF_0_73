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
    virtual void draw(float scale) = 0;
    virtual void move() = 0;
    virtual void detectGravitatorCollisions();
    virtual void collisionData(int collision);
    virtual void orientToPlanet(int collision);
    void gravitatorBounce();
    virtual void checkState();
    virtual void drawGUIOverlay(ofVec2f _pos, string text);
    virtual void displayMessage(ofVec2f _pos, string text);
    float countdownTimer(float timer);

    /// Getters & Setters
    ofVec2f getVelocity() const { return v; }
    int getVelocityLimit() const { return v_limit_in_space; }
    ofVec2f getNormalizedCollisionNormal() const { return normalized_collision_normal; }

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
    string gravitator_type;

protected:

    ofVec2f planet_pos;
    ofVec2f collision_normal;
    ofVec2f normalized_collision_normal;
    ofVec2f collision_perpendicular;
    float planet_m;
    float planet_r;
    int astronaut_pickup_range;
    int astronaut_drop_range;
    int spring_strength;

    int v_limit;
    int v_limit_in_gravity;
    int v_limit_in_space;

private:



};

#endif // ASTRONAUT_H
