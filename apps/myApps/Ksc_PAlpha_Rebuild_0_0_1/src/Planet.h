#ifndef PLANET_H
#define PLANET_H

#include "Gravitator.h"

//create a new animation. This could be done optinally in your code andnot as a static, just by saying animation_t walkAnimation; walkAnimation.index =0, walkAnimation.frame=0 etc. I find this method the easiest though



class Planet : public Gravitator {
public:
    Planet();
    Planet(ofVec2f _pos, int _r, int _m, int _gR);
    Planet(ofVec2f _pos, int _r, int _gR);

    virtual ~Planet();
    void setup();
    void draw();
    void update();



protected:
private:
};

#endif // PLANET_H
