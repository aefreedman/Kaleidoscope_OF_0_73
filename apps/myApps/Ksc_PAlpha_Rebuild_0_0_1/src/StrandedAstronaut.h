#ifndef STRANDEDASTRONAUT_H
#define STRANDEDASTRONAUT_H

#include "Astronaut.h"
#include <vector>

class StrandedAstronaut : public Astronaut {
public:
    StrandedAstronaut();
    StrandedAstronaut(ofVec2f _pos, std::vector<Gravitator *> *gravitator);

    virtual ~StrandedAstronaut();
    void update();
    void draw();
    void move();
    void detectPlayerCollisions();
    void followPlayer();
    void getPlayerData(ofVec2f _player_pos);

    bool FOLLOWING_PLAYER;

    std::vector<Gravitator *> *gravitator;

protected:

private:

    ofVec2f player_pos;


};

#endif // STRANDEDASTRONAUT_H
