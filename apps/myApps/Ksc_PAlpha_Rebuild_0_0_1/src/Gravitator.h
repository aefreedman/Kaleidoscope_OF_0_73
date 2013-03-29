#ifndef GRAVITATOR_H
#define GRAVITATOR_H

#include "GameObject.h"

class Gravitator : public GameObject {
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
    float G;
    int r;
    int gR;
    int m;
    float p;
    bool habitable;
    string type;

    vector <ofVec2f> pathPoints;

protected:
private:
};

#endif // GRAVITATOR_H
