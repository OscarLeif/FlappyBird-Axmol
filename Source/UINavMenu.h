//
// Created by oscar on 4/5/2024.
//

#ifndef FLAPPYBIRD_UINAVMENU_H
#define FLAPPYBIRD_UINAVMENU_H

#include "BetterButton.h"
#include "axmol.h"
#include "base/GameController.h"

USING_NS_AX;

class UINavMenu : public Node
{
public:
    UINavMenu();
    ~UINavMenu();
    static UINavMenu* create();
    bool init() override;
    void update(float delta) override;
    void setSelectedButton(BetterButton* button);
    BetterButton* getFocusButton();
    void initKeyboardListener();
    void RegisterControllerListener();
    // Static boolean variable to track input reading status
    static bool readingInput;
private:
    BetterButton* selectedButton;
    //Keyboard controller listener
    EventListenerKeyboard* keyboardListener;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    Scale9Sprite* indicator;
    //Gamepad controller listener
    void onConnectController(Controller *controller, Event *event);
    void onDisconnectedController(Controller *controller, Event *event);
    void resetControllerHolderState();
    void gamepadOnKeyDown(ax::Controller* controller, int keyCode, ax::Event* event);
    void gamepadOnKeyUp(ax::Controller* controller, int keyCode, ax::Event* event);
    void showButtonState(ax::Controller* controller, int keyCode, bool isPressed);

    float currentScale;
    bool scalingUp;
};

#endif  // FLAPPYBIRD_UINAVMENU_H
