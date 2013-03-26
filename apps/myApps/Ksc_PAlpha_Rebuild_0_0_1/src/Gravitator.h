#ifndef GRAVITATOR_H
#define GRAVITATOR_H

#include "GameObject.h"

class Gravitator : public GameObject {
public:
    Gravitator();
    Gravitator(ofVec2f _pos, int _r, int _m, int _gR);
    Gravitator(ofVec2f _pos, int _r, int _gR);
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual ~Gravitator();

    ofVec2f pos;
    int r;
    int gR;
    int m;
    float p;
    bool habitable;


protected:
private:
};

#endif // GRAVITATOR_H
