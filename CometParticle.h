#ifndef COMETPARTICLE_H
#define COMETPARTICLE_H


class CometParticle
{
    public:
        CometParticle();
        CometParticle(int _x, int _y, int _size);

        void setup();
        void update();
        void draw();
};

#endif // COMETPARTICLE_H
