#ifndef OFGRAVITYSOURCE_H
#define OFGRAVITYSOURCE_H

#include <ofMain.h>


class ofGravitySource {
public:
    void update();
    void draw();
    ofVec2f pos;
    float gPwr;
    float dim;
    ofGravitySource(ofVec2f pos, float dim, float gPwr);
    ~ofGravitySource();

protected:
private:
};

#endif // OFGRAVITYSOURCE_H
