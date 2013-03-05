#ifndef PLANET_H
#define PLANET_H

#include "Gravitator.h"


class Planet : public Gravitator
{
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
