#include "StrandedAstronaut.h"

StrandedAstronaut::StrandedAstronaut() : Astronaut()
{
    //ctor
}

StrandedAstronaut::StrandedAstronaut(ofVec2f _pos) : Astronaut(_pos) {}

StrandedAstronaut::~StrandedAstronaut()
{
    //dtor
}
/// TODO (Aaron#1#): Astronauts should sit and wait for the player, then follow the player when the player gets close enough to it
void StrandedAstronaut::update() {}
void StrandedAstronaut::draw() {}
void StrandedAstronaut::move() {}
