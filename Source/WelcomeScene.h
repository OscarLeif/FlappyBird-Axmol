//
// Created by oscar on 3/12/2024.
//

#ifndef FLAPPYBIRD_WELCOMESCENE_H
#define FLAPPYBIRD_WELCOMESCENE_H

#include "axmol.h"
#include "UINavMenu.h"
#include "extensions/axmol-ext.h"
#if AX_ENABLE_EXT_IMGUI
#include "Inspector/Inspector.h"
#endif
using namespace ax;
USING_NS_AX_EXT;

class WelcomeScene :public ax::Scene
{
public:
    void update(float delta) override;

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool init() override;

    virtual bool onTouchBegan(ax::Touch* touch, ax::Event* event);
    virtual void onTouchEnded(ax::Touch*, ax::Event*);

    //touch interface

    //keyboard interface
    EventListenerKeyboard* keyboardListener;
    void initKeyboardListener();
private:
    UINavMenu* navMenu;
    ax::Sprite* _ground[3];
    ax::Rect boundingBox;
    bool touchLocked = false; // Flag to indicate if touch is locked
    // Gamepad controller listener
    void onConnectController(Controller* controller, Event* event);
    void onDisconnectedController(Controller* controller, Event* event);
    void resetControllerHolderState();
    void gamepadOnKeyDown(ax::Controller* controller, int keyCode, ax::Event* event);
    void gamepadOnKeyUp(ax::Controller* controller, int keyCode, ax::Event* event);
};


#endif //FLAPPYBIRD_WELCOMESCENE_H
