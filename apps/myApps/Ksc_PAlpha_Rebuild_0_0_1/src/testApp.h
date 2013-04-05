#pragma once

#include <vector>
#include <iostream>
#include "ofMain.h"
#include "GameObject.h"
#include "Gravitator.h"
#include "Comet.h"
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
#include "GUI.h"
#include "Message.h"
#include "LevelEditor.h"
#include "GUIOverlay.h"
#define nl '\n'
#define fps 60
#define screen_width 1280
#define screen_height 720

class testApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
		void addGravitator();
		void addStrandedAstronaut(ofVec2f _pos);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void moveCamera(string direction);
		void reset();
		void loadSound();

        void exportLevel();
        void importLevel();
        void importLevel(int levelID);

        std::vector<Gravitator *> gravitator;
        std::vector<StrandedAstronaut *> strandedAstronaut;
        std::vector<GUI *> gui;
        Player player;

        ofImage background;

        string clickState;
        string levelState;
        string new_gravitator_type;
        ofVec2f NEW_PLANET_POS;
        ofVec2f NEW_COMET_POS;
        int NEW_PLANET_R;
        int NEW_PLANET_GR;
        int NEW_PLANET_M;
        int NEW_COMET_R;
        int levelID;

        ofVec3f camera_pos;
        ofVec3f camera_target;
        ofVec3f camera_target_save;

    private:
        int planet_base_m;
        int planet_mass_multiplier;
        bool CAN_EDIT_LEVEL;
        ofSoundPlayer jupiterSound;
        ofSoundPlayer   backgroundSound;
        bool MOVE_CAMERA;
        bool CAMERA_SCALING;
        ofVec2f player_start_pos;

        float camera_lerp_speed;

        int iddqd;
        bool PAUSE;
        float view_scale;
        float view_scale_target;
        float default_view_scale;
        float view_lerp_speed;
        float map_view_scale_target;
        bool MAP_VIEW;
        bool LOAD_WITH_SOUND;

};
