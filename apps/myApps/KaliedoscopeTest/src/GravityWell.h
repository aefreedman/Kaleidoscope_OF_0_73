#ifndef GRAVITYWELL_H
#define GRAVITYWELL_H
#include "ofxBox2dBaseShape.h"

class GravityWell : public ofxBox2dBaseShape {
public:
    GravityWell();
    virtual ~GravityWell();
    void setup();
    virtual void draw();
protected:
private:
};

#endif // GRAVITYWELL_H
