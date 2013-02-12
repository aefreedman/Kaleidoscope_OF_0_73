#include "Circle.h"

Circle::DrawCircle(float x, float y, float radius)
{
    ofCircle(x, y, radius);
}

Circle::~Circle()
{
    //dtor
}
