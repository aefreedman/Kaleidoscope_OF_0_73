#pragma once
#include "ofMain.h"
#include "Screen.h"
#include "GameScreen.h"
#include "MenuScreen.h"

class testApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

        void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        float countdownTimer(float time);

		ofSoundPlayer fx;
		Screen * currentScreen;
		GameScreen gameScreen;
		MenuScreen menuScreen;

		bool STARTED;
		float start_timer;
		float timer;

    private:


};
