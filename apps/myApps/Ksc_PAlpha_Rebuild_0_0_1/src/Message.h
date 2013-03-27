#ifndef MESSAGE_H
#define MESSAGE_H

#include "GUI.h"


class Message : public GUI
{
    public:
        Message();
        Message(ofVec2f _pos);
        virtual ~Message();
        void update();
        void draw();
    protected:
    private:
};

#endif // MESSAGE_H
