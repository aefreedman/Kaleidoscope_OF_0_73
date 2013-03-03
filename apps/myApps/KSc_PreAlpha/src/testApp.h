#pragma once

#include "ofMain.h"
#include "Planet.h"
#include "Player.h"
#include "Wall.h"

class testApp : public ofBaseApp{

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
    
    void addPlanet(ofPoint _location, int _size, int _gravRange);
    void addWall(ofPoint _location, int _width, int _height);
    float pointDist(ofPoint _p1, ofPoint _p2);
    
    void exportLevel();
    void importLevel();
    
    vector <Planet> planets;
    vector <Wall> walls;
    Player player;
    
    string clickState;
    string levelState;
    
    ofPoint planetPoint;
    int planetSize;
    int planetGrav;
    
    int levelID;
    
    bool planetHabitability;
    
    ofPoint wallPoint;
    int wallWidth;
    int wallHeight;
		
};
