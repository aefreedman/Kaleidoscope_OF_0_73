#include "ofMain.h"

class Screen
{
    public:
        Screen();
        Screen(int _r, int _g, int _b);

        virtual void setup();
        virtual void update();
        virtual void draw();

    protected:
    private:
};
