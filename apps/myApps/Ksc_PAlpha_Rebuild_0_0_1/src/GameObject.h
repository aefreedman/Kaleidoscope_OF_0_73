#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "ofMain.h"

class GameObject {
public:
    GameObject();
    virtual ~GameObject();
    virtual void update() = 0;
    virtual void draw() = 0;
protected:
private:
};

#endif // GAMEOBJECT_H
