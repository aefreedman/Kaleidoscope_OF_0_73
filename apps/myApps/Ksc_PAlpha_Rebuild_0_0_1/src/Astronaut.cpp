#include "Astronaut.h"
#define dt 1.0/60.0

Astronaut::Astronaut() {
    //ctor
}

Astronaut::Astronaut(ofVec2f _pos) {
    pos = _pos;
    attractor = 0;
}
Astronaut::Astronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator) : gravitator(gravitator) {
    pos = _pos;
    attractor = 0;
}

void Astronaut::checkState() {}

void Astronaut::detectGravitatorCollisions() {

}

float Astronaut::countdownTimer(float timer) {
    timer -= dt;
    return timer;
}
void Astronaut::collisionData(int collision) {
    planet_pos                          = (*gravitator)[collision]->pos;
    planet_m                            = (*gravitator)[collision]->m;
    planet_r                            = (*gravitator)[collision]->r;
    collision_normal.set(pos - planet_pos);
    normalized_collision_normal         = collision_normal.getNormalized();
    collision_perpendicular             = collision_normal.getPerpendicular();
    left                                = collision_perpendicular;
    right                               = -collision_perpendicular;
    gravitator_type                     = (*gravitator)[collision]->type;

}
void Astronaut::orientToPlanet(int collision) {

}
void Astronaut::gravitatorBounce() {
    if (v.length() < 0.05) {
        //v.set(0, 0);
    }
    float a1 = v.dot(normalized_collision_normal);
    float optimizedP = (2.0 * a1) / (m + planet_m);
    ofVec2f v_prime = v - optimizedP * planet_m * normalized_collision_normal;
    v_prime *= restitution;
    v.set(v_prime);


}

void Astronaut::drawGUIOverlay(ofVec2f _pos, string text) {
    //(*gui).push_back(new GUIOverlay(_pos, text));
    //(*gui).push_back(new Message(_pos + ofVec2f(0, -15), text));
}
void Astronaut::displayMessage(ofVec2f _pos, string text) {

}

Astronaut::~Astronaut() {
    //dtor
}
