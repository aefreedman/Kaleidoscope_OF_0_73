#ifndef _OF_BALL
#define _OF_BALL

#include <ofMain.h>


class ofBall {
public:
    void update();
    void draw();
    ofVec2f pos;
    float velY;
    float velX;
    int dim;
    ofBall(ofVec2f pos, int dim);
    ~ofBall();

protected:

private:
};

#endif // OFBALL_H
