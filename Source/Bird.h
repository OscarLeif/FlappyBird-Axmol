//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_BIRD_H
#define FLAPPYBIRD_BIRD_H

#include "axmol.h"

USING_NS_AX;

class Bird : public Sprite {
private:
    // Pointers to store our cached actions
    Action* _idle;
    Action* _swing;
    Action* _fly;

    // Static ID to keep bird color consistent across restarts
    static int _birdId;

public:
    // Constructor and Destructor
    Bird();
    virtual ~Bird();

    static Bird* create();
    virtual bool init() override; // Added override for clarity

    // State control methods
    void idle();
    void stop();
    void fly();
};

#endif //FLAPPYBIRD_BIRD_H
