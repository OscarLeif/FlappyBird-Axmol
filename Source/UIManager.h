//
// Created by oscar on 4/5/2024.
//

#ifndef FLAPPYBIRD_UIMANAGER_H
#define FLAPPYBIRD_UIMANAGER_H

#include "BetterButton.h"
#include "axmol.h"

USING_NS_AX;

class UIManager {
public:
    static UIManager* getInstance();
    UIManager();
    void setFocusedButton(BetterButton* button);
    BetterButton* getFocusedButton() const;
    void initKeyboardListener();
private:
    BetterButton* focusedButton;
    EventListenerKeyboard* keyboardListener;    
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    Sprite* reticle;  // Reticle sprite
};



#endif //FLAPPYBIRD_UIMANAGER_H
