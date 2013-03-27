#ifndef SHELL_H
#define SHELL_H

#include "ofMain.h"

class Shell {
public:
    Shell();
    virtual ~Shell();
    virtual void update() = 0;
protected:
private:
};

#endif // SHELL_H
