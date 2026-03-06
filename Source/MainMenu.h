//
// Created by oscar on 06/03/2026.
//

#ifndef FLAPPYBIRD_MAINMENU_H
#define FLAPPYBIRD_MAINMENU_H

#include "axmol.h"
USING_NS_AX;

class Scene;

class MainMenu: public ax::Scene {
public:
    bool init() override;
    void update(float dt) override;
    MainMenu();
    ~MainMenu() override;
private:
    int frameCounter;
};
#endif //FLAPPYBIRD_MAINMENU_H
