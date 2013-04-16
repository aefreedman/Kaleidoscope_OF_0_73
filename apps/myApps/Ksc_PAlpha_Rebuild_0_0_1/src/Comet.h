#ifndef COMET_H
#define COMET_H
#include "ofMain.h"
#include "Gravitator.h"

class Comet : public Gravitator {
public:
    Comet();
    Comet(ofVec2f _pos, int _r);
    Comet(ofVec2f _pos, int _r, vector <ofVec2f> _pathPoints);

    void setup();
    void update();
    void draw();

    void spawnParticle();

    //vector <ofVec2f> pathPoints;

    ofVec2f destination;
    int currentDest;
    ofVec2f dir;
    float vel;

    vector <ofVec3f> ptclPosSize;
    vector <ofColor> ptclColor;
    vector <ofVec2f> ptclDir;
    int spawnTimer;

    virtual ~Comet();
protected:
private:
};

#endif // COMET_H
