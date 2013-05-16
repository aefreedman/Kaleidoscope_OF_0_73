#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "Screen.h"
#include "GUIFadeOut.h"
#include "GUIFadeIn.h"

class EndScreen : public Screen
{
    public:
        EndScreen();
        virtual ~EndScreen();
        void setup();
        void update();
        void draw();
        void reset();

        float GetTimer() { return timer; }
        void SetTimer(float val) { timer = val; }
        bool GetLeaveScreen() { return LEAVE_SCREEN; }

        void keyPressed(int key);
        GUIFadeIn fadeIn;
        GUIFadeOut fadeOut;
    protected:
    private:
        void loadResources();
        float timer;
        bool TRANSITION_OUT;
        bool LEAVE_SCREEN;



        ofImage image;
};

#endif // ENDSCREEN_H
