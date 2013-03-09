#pragma once

#include "ofMain.h"
#include "Gravitator.h"
#include "Planet.h"
#include "Sun.h"
#include "BlackHole.h"
#include "Astronaut.h"
#include "Player.h"
#include "StrandedAstronaut.h"
#include "Decor.h"
#include "Shell.h"
#include "Solid.h"
#include "Nonsolid.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void addGravitator(ofVec2f _pos, int _r, int _m, int _gR, bool _habitable);

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
        Gravitator** gravitator;
        int nGravitators;
        Sun planet2;
        Player a;

};
