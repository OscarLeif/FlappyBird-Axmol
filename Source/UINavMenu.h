//
// Created by oscar on 4/5/2024.
//

#ifndef FLAPPYBIRD_UINAVMENU_H
#define FLAPPYBIRD_UINAVMENU_H

#include "BetterButton.h"
#include "axmol.h"

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
private:
    BetterButton* selectedButton;
    EventListenerKeyboard* keyboardListener;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    Scale9Sprite* indicator;

    float currentScale;
    bool scalingUp;
};

#endif  // FLAPPYBIRD_UINAVMENU_H
