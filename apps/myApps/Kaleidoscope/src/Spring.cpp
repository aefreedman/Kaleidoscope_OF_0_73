#include "spring.h"

Spring::Spring(float _x, float _y, int _s, float _d, float _m, float _k_in, Spring _others[NSPRINGS], int _id)
{
    size        = 20;

    k           = 0.2;

    velx        = 0.0;
    vely        = 0.0;
    accel       = 0;
    force       = 0;
}
