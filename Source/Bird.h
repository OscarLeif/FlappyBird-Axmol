//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_BIRD_H
#define FLAPPYBIRD_BIRD_H

#include "axmol.h"

USING_NS_AX;

class Bird :public Sprite{
private:
    Action* _idle;
    Action* _swing;
    Action* _fly;
    static int _birdId;

public:
    static Bird* create();
    virtual bool init();
    void idle();
    void stop();
    void fly();
};


#endif //FLAPPYBIRD_BIRD_H
