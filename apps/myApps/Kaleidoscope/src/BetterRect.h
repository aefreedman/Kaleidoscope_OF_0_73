#ifndef BETTERRECT_H
#define BETTERRECT_H

#include "BaseShape.h"


class BetterRect : public BaseShape
{
    public:
        BetterRect(ofVec2f _pos, float _w, float _h);
        virtual ~BetterRect();
        void draw();
    protected:
    private:
};

#endif // BETTERRECT_H
