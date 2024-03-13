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

    //touch interface

    //keyboard interface
private:
    ax::Sprite* _ground[2];
};


#endif //FLAPPYBIRD_WELCOMESCENE_H
