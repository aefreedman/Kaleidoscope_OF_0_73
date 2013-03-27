#include "Astronaut.h"

Astronaut::Astronaut() {
    //ctor
}

Astronaut::Astronaut(ofVec2f _pos) {
    pos = _pos;
    SIMPLE_GRAVITY = true;
}

void Astronaut::detectGravitatorCollisions() {

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
}
void Astronaut::orientToPlanet(int collision) {

}
void Astronaut::bounce() {
    float a1 = v.dot(normalized_collision_normal);
    float optimizedP = (2.0 * a1) / (m + planet_m);
    ofVec2f v_prime = v - optimizedP * planet_m * normalized_collision_normal;
    v_prime *= restitution;

    if (!CAN_LAND_ON_PLANET){
        v.set(v_prime);
    }
}
void Astronaut::calculateGravity(int attractor) {

}

Astronaut::~Astronaut() {
    //dtor
}
