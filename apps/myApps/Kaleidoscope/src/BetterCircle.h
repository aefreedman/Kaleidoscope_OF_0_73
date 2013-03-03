#ifndef BETTERCIRCLE_H
#define BETTERCIRCLE_H

#include "BaseShape.h"

class BetterCircle : public BaseShape
{
    public:
    BetterCircle(ofVec2f _pos, int _r);

    void draw();
};

#endif // BETTERCIRCLE_H
