#ifndef SUN_H
#define SUN_H

#include "Gravitator.h"


class Sun : public Gravitator {
public:
    Sun();
    Sun(ofVec2f _pos, int _r, int _m, int _gR);
    //Sun(ofVec2f _pos, int _r, int _gR);
    void setup();
    void draw();
    void update();
    virtual ~Sun();
protected:
private:
};

#endif // SUN_H
