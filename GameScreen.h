#include "Screen.h"


class GameScreen : public Screen
{
    public:
        GameScreen();
        void setup();
        void update();
        void draw();

        void changeScreen(Screen screen);



    protected:
    private:
};

