#ifndef GRAVITATOR_H
#define GRAVITATOR_H

#include "ofMain.h"


class Gravitator {
public:
    Gravitator();
    Gravitator(ofVec2f _pos, int _r, int _m, int _gR);
    Gravitator(ofVec2f _pos, int _r, int _gR);
    Gravitator(ofVec2f _pos, int _r);
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

    vector <ofVec2f> pathPoints;


protected:
private:
};

#endif // GRAVITATOR_H
