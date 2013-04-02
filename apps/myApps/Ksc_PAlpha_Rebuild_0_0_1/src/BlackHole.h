#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "Gravitator.h"


class BlackHole : public Gravitator {
public:
    BlackHole();
    BlackHole(ofVec2f _pos, int _r, int _m, int _gR);
    void setup();
    void update();
    void draw();
    virtual ~BlackHole();

    // TODO (Aaron#1#): blackhole should have super strong gravity
protected:
private:
};

#endif // BLACKHOLE_H
