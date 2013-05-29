#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
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
#include "GUIFadeIn.h"
#include "Message.h"
#include "LevelEditor.h"
#include "GUIOverlay.h"
#define nl '\n'
#define fps 60
#define number_of_stars 10000

class GameScreen : public Screen {
public:
    GameScreen();
    virtual ~GameScreen();

        void setup();
		void update();
		void draw();
		void renderSprites();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

        void exportSessionData();
        void exit();

		void addGravitator(ofVec2f pos, int r, int gR, int m);
		void addStrandedAstronaut(ofVec2f _pos, string _name);
		void camera();
		void reset();
		void loadSound();
		void drawGUI();

        void exportLevel();
        void importLevel();
        void importLevel(int levelID);

        /// Getters & Setters
		ofVec2f getLocalPosition(ofVec2f global_pos);
		ofVec2f getGlobalPosition(ofVec2f local_pos);
        bool isGameOver() const;
        int getLevel() const;
        void setLevel(int level_number);
        void setGameOver(bool _gameOver);
        void setCameraLerpSpeed(int speed) { camera_lerp_speed = speed; }
        void setCameraViewScaleTarget(float scale) { view_scale_target = scale; }
        float getCameraViewScale() const { return view_scale; }

        std::vector<Gravitator *> gravitator;
        std::vector<StrandedAstronaut *> strandedAstronaut;
        std::vector<Ghost *> ghosts;
        std::vector<GUI *> gui;
        int astronautsFollowing;
        Player player;
        int totalCrew;

        ofImage background;

        //HUD ASSETS
            ofImage O2frame;
            ofImage O2bar;
            ofTrueTypeFont text;

        ofxSpriteSheetRenderer * planetRenderer;
        ofxSpriteSheetRenderer * nautRenderer;
        bool CONTINUOUS_CAMERA;

        /// Level Editor
        string clickState;
        string levelState;
        string new_gravitator_type;
        ofVec2f NEW_PLANET_POS;
        ofVec2f NEW_COMET_POS;
        int NEW_PLANET_R;
        int NEW_PLANET_GR;
        int NEW_PLANET_M;
        int NEW_COMET_R;
        string new_astronaut_name;

        ofVec3f camera_pos;
        ofVec3f camera_target;
        ofVec3f camera_independent_target;
        ofVec3f camera_target_save;

        GUIFadeIn fadeIn;
        bool ENABLE_EDITOR;

protected:
private:
        int levelID;

        void drawLevelEditorGUI();
        void setCameraTarget(ofVec2f target);
        void moveCameraTarget(ofVec2f direction);
        void getState();
        void screenshot();
        void generateStars();
        void loadResources();
        void clearMetrics();
        ofVec2f getPlayerDirection();
        bool checkAllAstronautsDead();
        int pickLivingAstronaut();

        int planet_base_m;
        int planet_mass_multiplier;

        bool USING_LEVEL_EDITOR;
        bool MOVE_CAMERA;
        bool CAMERA_SCALING;
        bool MAP_VIEW;
        bool WON_LEVEL;
        bool LEVEL_HAS_ASTRONAUTS;
        bool MOVE_MESSAGES;
        bool PAUSE;
        bool PLACING_SOMETHING;
        bool CAN_MOVE_CAM;
        bool AN_ASTRONAUT_DIED;
        bool FREEZE_PLAYER;
        bool GAME_OVER;
        bool HIT_PAUSE;
        bool SCREEN_SHAKE;
        bool LOST_LEVEL;

        ofSoundPlayer jupiterSound;
        ofSoundPlayer backgroundSound;

        ofVec2f player_start_pos;

        std::vector<ofVec4f> stars;
        std::vector<ofVec4f> stars_dark;

        int iddqd;

        float camera_lerp_speed;
        static const float camera_lerp_speed_init = 4;
        float view_scale;
        float view_scale_target;
        static const float default_view_scale = 1.0;
        float view_lerp_speed;
        float map_view_scale_target;
        float level_over_timer_start;
        float level_over_timer;
        float hit_pause_timer;
        static const float hit_pause_timer_init = 0.4;
        float screen_shake_timer;
        static const float screen_shake_timer_init = 0.10;
        static const float screen_shake_max = 150.0;
        static const float lost_level_delay_time = 5.0;
        int astronautTarget;

        ofVec3f topRightCorner;
        ofVec3f bottomRightCorner;
        ofVec3f bottomLeftCorner;
        ofVec3f topLeftCorner;

        /// Metrics
        std::vector<ofVec4f> metric_playerDeaths;
        std::vector<string> metric_playerDeaths_cause;
        //std::vector<int> metric_playerJetpackUses;
};

#endif // GAMESCREEN_H
