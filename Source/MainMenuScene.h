//
// Created by oscar on 3/12/2024.
//

#ifndef FLAPPYBIRD_MAINMENUSCENE_H
#define FLAPPYBIRD_MAINMENUSCENE_H

#include "axmol.h"

class MainMenuScene : public ax::Scene
{
public:
    bool init() override;
    void update(float delta) override;

    //touch interface

    //keyboard interface
private:
    ax::Sprite* _ground[2];
};


#endif //FLAPPYBIRD_MAINMENUSCENE_H
