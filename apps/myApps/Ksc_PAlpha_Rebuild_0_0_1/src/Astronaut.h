#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "ofMain.h"

class Astronaut
{
    public:
        Astronaut();
        Astronaut(ofVec2f _pos);
        virtual ~Astronaut();

        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void move() = 0;

        ofVec2f pos;
        ofVec2f v;
        ofVec2f a;

        int w;
        int h;
    protected:
    private:
};

#endif // ASTRONAUT_H
