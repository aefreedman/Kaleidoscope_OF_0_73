#ifndef STRANDEDASTRONAUT_H
#define STRANDEDASTRONAUT_H

#include "Astronaut.h"
#include "Shell.h"
#include <vector>

class StrandedAstronaut : public Astronaut {
public:
    StrandedAstronaut();
    StrandedAstronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator, std::vector<StrandedAstronaut *> *strandedAstronaut, std::vector<GUI *> *gui);

    virtual ~StrandedAstronaut();
    void update();
    void draw();
    void move();
    void checkState();
    void bounce(int other);

    void detectGravitatorCollisions();
    void collisionData(int collision);
    void orientToPlanet(int collision);
    void calculateGravity(int attractor);
    void displayMessage();
    bool displayMessageTimer();
    string pickMessage();

    void detectPlayerCollisions();
    void followPlayer();
    void getPlayerData(ofVec2f _player_pos);

    bool FOLLOWING_PLAYER;
    bool CAN_TALK;

    string type;
    int id;

    std::vector<Gravitator *> *gravitator;
    std::vector<GUI *> *gui;
    std::vector<StrandedAstronaut *> *strandedAstronaut;

protected:

private:
    int message_display_chance;
    int message_dieroll;
    float message_timer;
    int message_delay;
    ofVec2f player_pos;

    bool DRAW_MESSAGE;

    int sa_collision;
    float lerp_speed;


};

#endif // STRANDEDASTRONAUT_H
