//
// Created by oscar on 3/12/2024.
//

#include "WelcomeScene.h"
#include "ui/axmol-ui.h"
#include "audio/AudioEngine.h"
#include "BetterButton.h"

USING_NS_AX;

#include "Bird.h"
#include "WorldScene.h"
#include "AtaMath.h"
#include "UINavMenu.h"

bool WelcomeScene::init()
{
    if (!Scene::init())
        return false;

    auto world = Node::create();
    addChild(world);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();

    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("flappy.plist");

    // Add background
    auto background = Sprite::createWithSpriteFrameName("background_day.png");
    // position the background on the center of the screen
    //        background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setWorldPosition(Vec2::ZERO);
    // add the background as a child to this layer
    world->addChild(background, 0);

    boundingBox = background->getBoundingBox();

    // Add ground
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

    _ground[0]->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0), AtaMath::interpolate(minY, maxY, 0)));
    _ground[1]->setPosition(
        Vec2(AtaMath::interpolate(minX, maxX, 0) + groundSize.width, AtaMath::interpolate(minY, maxY, 0)));

    world->addChild(_ground[0], 1);
    world->addChild(_ground[1], 1);

    auto title = Sprite::createWithSpriteFrameName("label_flappy_bird.png");
    //        title->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*2.0/3 + origin.y));
    title->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, 0.75)));

    world->addChild(title);

    navMenu = UINavMenu::create();

    // Create play button
    // auto play = ax::ui::Button::create("button_play_normal.png", "button_play_pressed.png", "",
    // ax::ui::Widget::TextureResType::PLIST);
    auto play =
        BetterButton::create("button_play_normal.png", "button_play_pressed.png", Widget::TextureResType::PLIST);
    play->setName("PlayBt");
    //        play->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));
    play->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    play->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, .45)));

    play->addClickEventListener([&](Ref* sender) {
        AudioEngine::play2d("sfx_swooshing.wav");
        TransitionScene* transition = TransitionFade::create(0.75f, WorldScene::create());
        navMenu->getParent()->removeChild(navMenu);
        Director::getInstance()->replaceScene(transition);
    });


    auto exit = BetterButton::create("indicator.png", "", Widget::TextureResType::LOCAL);
    exit->setName("exit");
    exit->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, .35)));

    play->downButton = exit;
    exit->upButton   = play;

    addChild(play);
    addChild(exit);

    auto bird = Bird::create();
    //        bird->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bird->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, 0.60)));
    bird->idle();
    world->addChild(bird);

    // The listener should be disable on play mode.
    // UINavMenu::getInstance()->initKeyboardListener();

    // Schedule update to be called per frame
    scheduleUpdate();

    // Enable touch events
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = AX_CALLBACK_2(WelcomeScene::onTouchBegan, this);
    listener->onTouchEnded = AX_CALLBACK_2(WelcomeScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // UINavMenu::getInstance()->initKeyboardListener();
    // UINavMenu::getInstance()->setFocusedButton(play);
    addChild(navMenu);

    navMenu->initKeyboardListener();
    navMenu->setSelectedButton(play);

    return true;
}

void WelcomeScene::update(float delta)
{
    float groundWidth = _ground[0]->getContentSize().width;
    for (int i = 0; i < 2; i++)
    {
        _ground[i]->setPositionX(_ground[i]->getPositionX() - 2.0f);

        if (_ground[i]->getPositionX() < -groundWidth)
            _ground[i]->setPositionX(_ground[i]->getPositionX() + 2 * groundWidth);
    }

    auto camera = Camera::getDefaultCamera();
    camera->setWorldPosition(Vec2::ZERO);

    Size visibleSize        = Director::getInstance()->getVisibleSize();
    float boundingBoxHeight = boundingBox.size.height;

    bool isLandscape = (visibleSize.width / visibleSize.height) > 1;
    // Calculate the desired zoom factor
    float desiredHeight = isLandscape ? visibleSize.height * 0.5 : visibleSize.width * 0.35;
    float zoomFactor    = desiredHeight / boundingBoxHeight;

    camera->setZoom(zoomFactor);
}

bool WelcomeScene::onTouchBegan(Touch* touch, Event* event)
{
    if (touchLocked)
    {
        // Touch is already locked, ignore new touches
        return false;
    }

    // Lock the touch
    touchLocked = true;

    // Get the touch location
    Vec2 touchLocation = touch->getLocation();

    // Get the screen size
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto Camera     = ax::Camera::getDefaultCamera();
    float increment = 0.1f;

    // Check if the touch occurred on the left side of the screen
    if (touchLocation.x < visibleSize.width / 2)
    {
        // Touch on the left side
        AXLOG("Touch on the left side of the screen");
        float newZoom = Camera->getZoom() - increment;
        Camera->setZoom(newZoom);
    }
    // Check if the touch occurred on the right side of the screen
    else
    {
        // Touch on the right side
        AXLOG("Touch on the right side of the screen");
        float newZoom = Camera->getZoom() + increment;
        Camera->setZoom(newZoom);
    }

    return true;
}

void WelcomeScene::onTouchEnded(Touch* touch, Event* event)
{
    // Unlock the touch
    touchLocked = false;
}
