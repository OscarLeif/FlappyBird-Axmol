//
// Created by oscar on 4/5/2024.
//

#include "BetterButton.h"


BetterButton* BetterButton::create(std::string normalImage, std::string selectedImage)
{
    auto button = new (std::nothrow) BetterButton();
    if (button && button->init(normalImage, selectedImage)) {
        button->autorelease();
        return button;
    }
    AX_SAFE_DELETE(button);
    return nullptr;
}

bool BetterButton::init(std::string normalImage, const std::string selectedImage) {
    if (!Button::init(normalImage, selectedImage, "", ax::ui::Widget::TextureResType::PLIST)) {
        return false;
    }

    // Additional initialization specific to BetterButton
    int sum = 1+1;

    return true;
}

void BetterButton::TriggerEventClick()
{
    if (_clickEventListener)
    {
        _clickEventListener(this);
    }
}
