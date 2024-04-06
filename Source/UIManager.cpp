//
// Created by oscar on 4/5/2024.
//

#include "UIManager.h"

UIManager* UIManager::getInstance() {
    static UIManager* instance;
    return instance;
}

void UIManager::initKeyboardListener()
{
    auto keyboardListener1 = EventListenerKeyboard::create();
    keyboardListener1->onKeyPressed = AX_CALLBACK_2(UIManager::onKeyPressed, this);
    keyboardListener1->onKeyReleased= AX_CALLBACK_2(UIManager::onKeyReleased, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener1, 1);
}

void UIManager::setFocusedButton(BetterButton* button)
{
    if(button != nullptr)
    {
        focusedButton = button;
        AXLOG("The value is: %s", button->getName());
    }
    else
    {
        AXLOG("Cannot set a Null Reference");
    }
}

BetterButton* UIManager::getFocusedButton() const {
    return focusedButton;
}

void UIManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case ax::EventKeyboard::KeyCode::KEY_NONE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_PAUSE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_SCROLL_LOCK:
        break;
    case ax::EventKeyboard::KeyCode::KEY_PRINT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_SYSREQ:
        break;
    case ax::EventKeyboard::KeyCode::KEY_BREAK:
        break;
    case ax::EventKeyboard::KeyCode::KEY_ESCAPE:
        break;
    /*case ax::EventKeyboard::KeyCode::KEY_BACK:
        break;*/
    case ax::EventKeyboard::KeyCode::KEY_BACKSPACE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_TAB:
        break;
    case ax::EventKeyboard::KeyCode::KEY_BACK_TAB:
        break;
    case ax::EventKeyboard::KeyCode::KEY_RETURN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPS_LOCK:
        break;
    case ax::EventKeyboard::KeyCode::KEY_SHIFT:
        break;
    /*case ax::EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
        break;*/
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CTRL:
        break;
    /*case ax::EventKeyboard::KeyCode::KEY_LEFT_CTRL:
        break;*/
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_CTRL:
        break;
    case ax::EventKeyboard::KeyCode::KEY_ALT:
        break;
    /*case ax::EventKeyboard::KeyCode::KEY_LEFT_ALT:
        break;*/
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_ALT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_MENU:
        break;
    case ax::EventKeyboard::KeyCode::KEY_HYPER:
        break;
    case ax::EventKeyboard::KeyCode::KEY_INSERT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_HOME:
        break;
    case ax::EventKeyboard::KeyCode::KEY_PG_UP:
        break;
    case ax::EventKeyboard::KeyCode::KEY_DELETE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_END:
        break;
    case ax::EventKeyboard::KeyCode::KEY_PG_DOWN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_LEFT_ARROW:

        break;
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        break;
    case ax::EventKeyboard::KeyCode::KEY_UP_ARROW:
        setFocusedButton(this->focusedButton->upButton);
        break;
    case ax::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        setFocusedButton(this->focusedButton->downButton);
        break;
    case ax::EventKeyboard::KeyCode::KEY_NUM_LOCK:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_PLUS:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_MINUS:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_MULTIPLY:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_DIVIDE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_ENTER:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_HOME:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_UP:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_PG_UP:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_LEFT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_FIVE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_RIGHT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_END:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_DOWN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_PG_DOWN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_INSERT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_KP_DELETE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F1:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F2:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F3:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F4:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F5:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F6:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F7:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F8:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F9:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F10:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F11:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F12:
        break;
    case ax::EventKeyboard::KeyCode::KEY_SPACE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_EXCLAM:
        break;
    case ax::EventKeyboard::KeyCode::KEY_QUOTE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_NUMBER:
        break;
    case ax::EventKeyboard::KeyCode::KEY_DOLLAR:
        break;
    case ax::EventKeyboard::KeyCode::KEY_PERCENT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CIRCUMFLEX:
        break;
    case ax::EventKeyboard::KeyCode::KEY_AMPERSAND:
        break;
    case ax::EventKeyboard::KeyCode::KEY_APOSTROPHE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_LEFT_PARENTHESIS:
        break;
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_PARENTHESIS:
        break;
    case ax::EventKeyboard::KeyCode::KEY_ASTERISK:
        break;
    case ax::EventKeyboard::KeyCode::KEY_PLUS:
        break;
    case ax::EventKeyboard::KeyCode::KEY_COMMA:
        break;
    case ax::EventKeyboard::KeyCode::KEY_MINUS:
        break;
    case ax::EventKeyboard::KeyCode::KEY_PERIOD:
        break;
    case ax::EventKeyboard::KeyCode::KEY_SLASH:
        break;
    case ax::EventKeyboard::KeyCode::KEY_0:
        break;
    case ax::EventKeyboard::KeyCode::KEY_1:
        break;
    case ax::EventKeyboard::KeyCode::KEY_2:
        break;
    case ax::EventKeyboard::KeyCode::KEY_3:
        break;
    case ax::EventKeyboard::KeyCode::KEY_4:
        break;
    case ax::EventKeyboard::KeyCode::KEY_5:
        break;
    case ax::EventKeyboard::KeyCode::KEY_6:
        break;
    case ax::EventKeyboard::KeyCode::KEY_7:
        break;
    case ax::EventKeyboard::KeyCode::KEY_8:
        break;
    case ax::EventKeyboard::KeyCode::KEY_9:
        break;
    case ax::EventKeyboard::KeyCode::KEY_COLON:
        break;
    case ax::EventKeyboard::KeyCode::KEY_SEMICOLON:
        break;
    case ax::EventKeyboard::KeyCode::KEY_LESS_THAN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_EQUAL:
        break;
    case ax::EventKeyboard::KeyCode::KEY_GREATER_THAN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_QUESTION:
        break;
    case ax::EventKeyboard::KeyCode::KEY_AT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_A:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_B:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_C:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_D:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_E:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_F:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_G:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_H:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_I:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_J:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_K:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_L:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_M:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_N:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_O:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_P:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_Q:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_R:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_S:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_T:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_U:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_V:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_W:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_X:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_Y:
        break;
    case ax::EventKeyboard::KeyCode::KEY_CAPITAL_Z:
        break;
    case ax::EventKeyboard::KeyCode::KEY_LEFT_BRACKET:
        break;
    case ax::EventKeyboard::KeyCode::KEY_BACK_SLASH:
        break;
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_BRACKET:
        break;
    case ax::EventKeyboard::KeyCode::KEY_UNDERSCORE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_GRAVE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_A:
        break;
    case ax::EventKeyboard::KeyCode::KEY_B:
        break;
    case ax::EventKeyboard::KeyCode::KEY_C:
        break;
    case ax::EventKeyboard::KeyCode::KEY_D:
        break;
    case ax::EventKeyboard::KeyCode::KEY_E:
        break;
    case ax::EventKeyboard::KeyCode::KEY_F:
        break;
    case ax::EventKeyboard::KeyCode::KEY_G:
        break;
    case ax::EventKeyboard::KeyCode::KEY_H:
        break;
    case ax::EventKeyboard::KeyCode::KEY_I:
        break;
    case ax::EventKeyboard::KeyCode::KEY_J:
        break;
    case ax::EventKeyboard::KeyCode::KEY_K:
        break;
    case ax::EventKeyboard::KeyCode::KEY_L:
        break;
    case ax::EventKeyboard::KeyCode::KEY_M:
        break;
    case ax::EventKeyboard::KeyCode::KEY_N:
        break;
    case ax::EventKeyboard::KeyCode::KEY_O:
        break;
    case ax::EventKeyboard::KeyCode::KEY_P:
        break;
    case ax::EventKeyboard::KeyCode::KEY_Q:
        break;
    case ax::EventKeyboard::KeyCode::KEY_R:
        break;
    case ax::EventKeyboard::KeyCode::KEY_S:
        break;
    case ax::EventKeyboard::KeyCode::KEY_T:
        break;
    case ax::EventKeyboard::KeyCode::KEY_U:
        break;
    case ax::EventKeyboard::KeyCode::KEY_V:
        break;
    case ax::EventKeyboard::KeyCode::KEY_W:
        break;
    case ax::EventKeyboard::KeyCode::KEY_X:
        break;
    case ax::EventKeyboard::KeyCode::KEY_Y:
        break;
    case ax::EventKeyboard::KeyCode::KEY_Z:
        break;
    case ax::EventKeyboard::KeyCode::KEY_LEFT_BRACE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_BAR:
        break;
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_BRACE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_TILDE:
        break;
    case ax::EventKeyboard::KeyCode::KEY_EURO:
        break;
    case ax::EventKeyboard::KeyCode::KEY_POUND:
        break;
    case ax::EventKeyboard::KeyCode::KEY_YEN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_MIDDLE_DOT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_SEARCH:
        break;
    case ax::EventKeyboard::KeyCode::KEY_DPAD_LEFT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
        break;
    case ax::EventKeyboard::KeyCode::KEY_DPAD_UP:
        break;
    case ax::EventKeyboard::KeyCode::KEY_DPAD_DOWN:
        break;
    case ax::EventKeyboard::KeyCode::KEY_DPAD_CENTER:
        break;
    case ax::EventKeyboard::KeyCode::KEY_ENTER:
        this->focusedButton->
        break;
    case ax::EventKeyboard::KeyCode::KEY_PLAY:
        break;
    default:
        break;
    }
}
void UIManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    int dummy = 0;
}
