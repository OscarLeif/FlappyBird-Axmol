//
// Created by oscar on 4/5/2024.
//

#ifndef FLAPPYBIRD_BETTERBUTTON_H
#define FLAPPYBIRD_BETTERBUTTON_H


#include "axmol.h"
#include "ui/UIButton.h."
//#include "ui/CocosGUI.h"

USING_NS_AX;
using namespace ax::ui;

class BetterButton : public Button {
public:
    static BetterButton* create(const std::string normalImage, const std::string selectedImage);
    virtual bool init(const std::string normalImage, const std::string selectedImage);

    BetterButton* upButton;
    BetterButton* downButton;
    BetterButton* leftButton;
    BetterButton* righButton;

    void TriggerEventClick();
};

#endif //FLAPPYBIRD_BETTERBUTTON_H
