#ifndef STRANDEDASTRONAUT_H
#define STRANDEDASTRONAUT_H

#include "Astronaut.h"


class StrandedAstronaut : public Astronaut
{
    public:
        StrandedAstronaut();
        StrandedAstronaut(ofVec2f _pos);
        virtual ~StrandedAstronaut();


        void update();
        void draw();
        void move();
    protected:
    private:
};

#endif // STRANDEDASTRONAUT_H
