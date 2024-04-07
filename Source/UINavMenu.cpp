//
// Created by oscar on 4/5/2024.
//

#include "UINavMenu.h"
#include "ui/UIScale9Sprite.h"

UINavMenu::UINavMenu() : selectedButton(nullptr), keyboardListener(nullptr), indicator(nullptr), currentScale(0) {}

UINavMenu::~UINavMenu()
{
    indicator      = nullptr;
    selectedButton = nullptr;
    currentScale   = 1;
    scalingUp      = true;
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);
    keyboardListener = nullptr;
}

UINavMenu* UINavMenu::create()
{
    auto navMenu = new UINavMenu();
    if (navMenu && navMenu->Node::init() && navMenu->init())
    {
        return navMenu;
    }
    AX_SAFE_DELETE(navMenu);
    return nullptr;
}

bool UINavMenu::init()
{
    if (!Node::init())
    {
        return false;
    }
    indicator = Scale9Sprite::create("indicator.png");
    indicator->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    // indicator->setCenterRectNormalized(Rect(0.5f,0.5f,0.2f,0.2f));
    this->addChild(indicator, 100);
    this->scheduleUpdate();
    return true;
}

void UINavMenu::initKeyboardListener()
{
    keyboardListener= EventListenerKeyboard::create();
    keyboardListener->onKeyPressed  = AX_CALLBACK_2(UINavMenu::onKeyPressed, this);
    keyboardListener->onKeyReleased = AX_CALLBACK_2(UINavMenu::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void UINavMenu::setSelectedButton(BetterButton* iSelectButton)
{
    if (iSelectButton != nullptr)
    {
        selectedButton = iSelectButton;
        AXLOG("The value is: %s \n", iSelectButton->getName());
        // Set reticle scale to fit the selected button
        Size buttonSize = iSelectButton->getContentSize();
        //        indicator->setScale(buttonSize.width / indicator->getContentSize().width,
        //                          buttonSize.height / indicator->getContentSize().height);
        auto buttonBounds = iSelectButton->getBoundingBox();

        indicator->setContentSize(buttonSize);
        if (indicator != nullptr)
        {
            //            indicator->setWorldPosition(iSelectButton->getWorldPosition());
            /*Vec2 center = Vec2((buttonBounds.getMinX() + buttonBounds.getMaxX() / 2),
                               (buttonBounds.getMinY() + buttonBounds.getMaxY() / 2));*/
            Vec2 center =
                Vec2(buttonBounds.origin.x + buttonSize.width / 2, buttonBounds.origin.y + buttonSize.height / 2);

            // center += Vec2(buttonSize.width/2,buttonSize.height/2);
            indicator->setWorldPosition(center);
            // probably setup the Size
        }
    }
    else
    {
        AXLOG("Cannot set a Null Reference \n");
    }
}

BetterButton* UINavMenu::getFocusButton()
{
    if (!selectedButton)
        return nullptr;
    else
        return selectedButton;
}

void UINavMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        break;
    case ax::EventKeyboard::KeyCode::KEY_UP_ARROW:
        if (selectedButton != nullptr)
            setSelectedButton(this->selectedButton->upButton);
        break;
    case ax::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        if (selectedButton != nullptr)
            setSelectedButton(this->selectedButton->downButton);
        break;
    case ax::EventKeyboard::KeyCode::KEY_ENTER:
        if (selectedButton != nullptr)
            this->selectedButton->TriggerEventClick();
        break;
    default:
        break;
    }
}
void UINavMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    int dummy = 0;
}

void UINavMenu::update(float delta)
{
    const float targetScale = 1.1f;
    const float scaleSpeed  = 0.01f;  // Adjust as needed

    if (scalingUp)
    {
        currentScale += scaleSpeed;
        if (currentScale >= targetScale)
        {
            currentScale = targetScale;
            scalingUp    = false;
        }
    }
    else
    {
        currentScale -= scaleSpeed;
        if (currentScale <= 1.0f)
        {
            currentScale = 1.0f;
            scalingUp    = true;
        }
    }

    // AXLOG("Scale Reticle %f \n", currentScale);//forgot to initialize currentScale
    //  Apply the scale to your node
    indicator->setScale(currentScale);

    // Windows is not visible...
    if (selectedButton != nullptr)
    {
        // selectedButton->setScale(currentScale);
    }
}
