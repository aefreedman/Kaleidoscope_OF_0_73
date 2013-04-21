#ifndef COMET_H
#define COMET_H
#include "ofMain.h"
#include "Gravitator.h"

class Comet : public Gravitator {
public:
    Comet();
    Comet(ofVec2f _pos, int _r);
    Comet(ofVec2f _pos, int _r, vector <ofVec2f> _pathPoints);

    void setup();
    void update();
    void draw();

    void spawnParticle();

    //vector <ofVec2f> pathPoints;

    ofVec2f destination;
    int currentDest;
    ofVec2f dir;
    float vel;

    vector <ofVec3f> ptclPosSize;
    vector <ofColor> ptclColor;
    vector <ofVec2f> ptclDir;
    float spawnTimer;
    float spawnTimer_init;

    virtual ~Comet();
protected:
private:
    int particle_spawn_offset;
    double particle_max_size;
    double particle_min_size;
    double particle_pos_range;
    double particle_fade_rate;
    double particle_v;
    ofColor cometColor;
    int cometColor_a_min;
    int cometColor_a_max;
    int particles_per_frame;
};

#endif // COMET_H
