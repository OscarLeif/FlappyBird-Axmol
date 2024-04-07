//
// Created by oscar on 4/5/2024.
//

#include "BetterButton.h"

BetterButton::BetterButton() : leftButton(nullptr), righButton(nullptr), upButton(nullptr), downButton(nullptr) {}

BetterButton* BetterButton::create(std::string normalImage,
                                   std::string selectedImage,
                                   std::string disableImage,
                                   ax::ui::Widget::TextureResType textType)
{
    auto button = new (std::nothrow) BetterButton();
    if (button && button->init(normalImage, selectedImage, textType))
    {
        button->leftButton = nullptr;
        button->righButton = nullptr;
        button->upButton   = nullptr;
        button->downButton = nullptr;
        button->autorelease();
        return button;
    }
    AX_SAFE_DELETE(button);
    return nullptr;
}

bool BetterButton::init(std::string normalImage,
                        const std::string selectedImage,
                        ax::ui::Widget::TextureResType textType)
{
    if (!Button::init(normalImage, selectedImage, "", textType))
    {
        return false;
    }
    return true;
}

void BetterButton::TriggerEventClick()
{
    if (_clickEventListener)
    {
        _clickEventListener(this);
    }
}
