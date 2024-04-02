//
// Created by oscar on 3/12/2024.
//

#ifndef FLAPPYBIRD_WELCOMESCENE_H
#define FLAPPYBIRD_WELCOMESCENE_H

#include "axmol.h"

class WelcomeScene :public ax::Scene
{
public:
    bool init() override;
    void update(float delta) override;

    virtual bool onTouchBegan(ax::Touch* touch, ax::Event* event);
    virtual void onTouchEnded(ax::Touch*, ax::Event*);

    //touch interface

    //keyboard interface
private:
    ax::Sprite* _ground[2];
    ax::Rect boundingBox;
    bool touchLocked = false; // Flag to indicate if touch is locked
};


#endif //FLAPPYBIRD_WELCOMESCENE_H
