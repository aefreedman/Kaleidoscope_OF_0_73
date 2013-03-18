#pragma once

#include <vector>
#include <iostream>
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
		void addGravitator();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void exportLevel();
        void importLevel();

        std::vector<Gravitator *> gravitator;
        Player thePlayer;

        string clickState;
        string levelState;
        ofVec2f NEW_PLANET_POS;
        int NEW_PLANET_R;
        int NEW_PLANET_GR;
        int NEW_PLANET_M;

    int levelID;

    private:


};
