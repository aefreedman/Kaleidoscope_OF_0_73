#ifndef _OF_BALL
#define _OF_BALL

#include <ofMain.h>


class ofBall {
public:
    void update();
    void draw();
    ofVec2f pos;
    ofVec2f vel;
    int dim;
    int id;
    ofBall(ofVec2f pos, int dim, int id);
    ~ofBall();

protected:

private:

    //ofBall friends[5];

};

#endif // OFBALL_H
