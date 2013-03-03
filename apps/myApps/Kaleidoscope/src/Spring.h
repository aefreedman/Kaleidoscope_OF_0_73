#ifndef SPRING_H
#define SPRING_H

#include <ofMain.h>
#define NSPRINGS 5

class Spring
{
    public:
        float xpos, ypos;
        float tempxpos, tempypos;
        int size;
        bool over;
        bool move;

        //Spring
        float mass;
        float k;
        float damp;
        float rest_posx;
        float rest_posy;

        float pos;
        float velx;
        float vely;
        float accel;
        float force;

        //Spring friends[5];
        int me;


        Spring(float x, float y, int s, float d,
               float m, float k_in, Spring others[NSPRINGS], int _id);
        ~Spring();
    protected:
    private:
};

#endif // SPRING_H
