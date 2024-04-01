//
// Created by oscar on 3/12/2024.
//

#include "WelcomeScene.h"
#include "ui/axmol-ui.h"
#include "audio/AudioEngine.h"

USING_NS_AX;

#include "Bird.h"
#include "WorldScene.h"
#include "AtaMath.h"

bool WelcomeScene::init()
{
        if (!Scene::init())
            return false;

        auto world = Node::create();
        addChild(world);

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        auto spritecache = SpriteFrameCache::getInstance();
        spritecache->addSpriteFramesWithFile("flappy.plist");

        //Add background
        auto background = Sprite::createWithSpriteFrameName("background_day.png");
        // position the background on the center of the screen
//        background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        background->setWorldPosition(Vec2::ZERO);
        // add the background as a child to this layer
        world->addChild(background, 0);

        auto boundingBox =background->getBoundingBox();

        //Add ground
        _ground[0] = Sprite::createWithSpriteFrameName("ground.png");
        _ground[1] = Sprite::createWithSpriteFrameName("ground.png");

        auto groundSize = _ground[0]->getContentSize();

        _ground[0]->setAnchorPoint(Point::ZERO);
        _ground[1]->setAnchorPoint(Point::ZERO);

//        _ground[0]->setPosition(Point::ZERO);
//        _ground[1]->setPosition(Vec2(groundSize.width, 0));
        float minX = boundingBox.getMinX();
        float maxX = boundingBox.getMaxX();

        float minY = boundingBox.getMinY();
        float maxY = boundingBox.getMaxY();

        _ground[0]->setPosition(Vec2(AtaMath::interpolate(minX,maxX,0), AtaMath::interpolate(minY,maxY,0)));
        _ground[1]->setPosition(Vec2(AtaMath::interpolate(minX,maxX,0)+groundSize.width, AtaMath::interpolate(minY,maxY,0)));

        world->addChild(_ground[0], 1);
        world->addChild(_ground[1], 1);

        auto title = Sprite::createWithSpriteFrameName("label_flappy_bird.png");
//        title->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*2.0/3 + origin.y));
        title->setPosition(Vec2(AtaMath::interpolate(minX,maxX,0.5), AtaMath::interpolate(minY,maxY,0.75)));

        world->addChild(title);

        //Create play button
        auto play = ax::ui::Button::create("button_play_normal.png", "button_play_pressed.png", "", ax::ui::Widget::TextureResType::PLIST);
//        play->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));
        play->setPosition(Vec2(AtaMath::interpolate(minX,maxX,0.5), AtaMath::interpolate(minY,maxY,.45)));

        play->addClickEventListener([](Ref* sender) {
            AudioEngine::play2d("sfx_swooshing.wav");
            TransitionScene *transition = TransitionFade::create(0.75f, WorldScene::create());
            Director::getInstance()->replaceScene(transition);
        });

        addChild(play);

        auto bird = Bird::create();
//        bird->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        bird->setPosition(Vec2(AtaMath::interpolate(minX,maxX,0.5), AtaMath::interpolate(minY,maxY,0.60)));
        bird->idle();
        world->addChild(bird);

        //Schedule update to be called per frame
        scheduleUpdate();

        return true;
}

void WelcomeScene::update(float delta)
{
    float groundWidth = _ground[0]->getContentSize().width;
    for (int i=0; i<2; i++) {
        _ground[i]->setPositionX(_ground[i]->getPositionX() - 2.0f);

        if (_ground[i]->getPositionX() < -groundWidth)
            _ground[i]->setPositionX(_ground[i]->getPositionX() + 2*groundWidth);
    }

    auto camera = Camera::getDefaultCamera();
    camera->setWorldPosition(Vec2::ZERO);
}
