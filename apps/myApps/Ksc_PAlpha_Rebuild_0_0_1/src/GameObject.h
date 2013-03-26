#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "ofMain.h"

class GameObject {
public:
    GameObject();
    virtual ~GameObject();
    virtual void update();
    virtual void draw();
protected:
private:
};

#endif // GAMEOBJECT_H
