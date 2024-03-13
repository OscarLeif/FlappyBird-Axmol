//
// Created by oscar on 3/12/2024.
//

#include "WelcomeScene.h"
#include "ui/axmol-ui.h"

USING_NS_AX;

bool WelcomeScene::init()
{
    if (!Scene::initWithPhysics()) {
        return false;
    }

    auto visibleSize = _director->getVisibleOrigin();
    auto origin = _director->getVisibleOrigin();

    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("flappy.plist");

    auto background = ax::Sprite::createWithSpriteFrameName("background_day.png");
    // position the background on the center of the screen
    background->setPosition(ax::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the background as a child to this layer
    addChild(background, 0);

    //Add ground
    _ground[0] = Sprite::createWithSpriteFrameName("ground.png");
    _ground[1] = Sprite::createWithSpriteFrameName("ground.png");

    auto groundSize = _ground[0]->getContentSize();

    _ground[0]->setAnchorPoint(Point::ZERO);
    _ground[1]->setAnchorPoint(Point::ZERO);

    _ground[0]->setPosition(Point::ZERO);
    _ground[1]->setPosition(Vec2(groundSize.width, 0));

    addChild(_ground[0], 1);
    addChild(_ground[1], 1);

    auto title = Sprite::createWithSpriteFrameName("label_flappy_bird.png");
    title->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*2.0/3 + origin.y));

    addChild(title);

    //Create play button
    auto play = ax::ui::Button::create("button_play_normal.png", "button_play_pressed.png", "", ax::ui::Widget::TextureResType::PLIST);
    play->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));

    return true;
}

void WelcomeScene::update(float delta) {

}
