#ifndef BASESHAPE_H
#define BASESHAPE_H

#include <ofMain.h>


class BaseShape
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        int r;
        float damp;
        float w;
        float h;
        ofVec2f accel;
        BaseShape(ofVec2f _pos, ofVec2f _vel, float _damp);
        BaseShape(ofVec2f _pos, int _r);
        BaseShape(ofVec2f _pos, float _w, float _h);
        virtual ~BaseShape();
        void update();
        virtual void draw();
    protected:
    private:
};

#endif // BASESHAPE_H
