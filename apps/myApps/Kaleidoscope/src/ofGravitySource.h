#ifndef OFGRAVITYSOURCE_H
#define OFGRAVITYSOURCE_H

#include <ofMain.h>


class ofGravitySource {
public:
    void update();
    void draw();
    ofVec2f pos;
    float gPwr;
    int gRange;
    float r;
    ofVec2f vel;
    ofGravitySource(ofVec2f _pos, ofVec2f _vel, float _r, float _gPwr, int _gRange);
    ~ofGravitySource();

protected:
private:
};

#endif // OFGRAVITYSOURCE_H
