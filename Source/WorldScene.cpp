#include "WorldScene.h"
#include "ui/CocosGUI.h"
#include "GameOver.h"
#include "PhysicsHelper.h"
#include "Shake.h"
#include "audio/AudioEngine.h"
#include "AtaMath.h"

USING_NS_AX;
// using namespace CocosDenshion;
using namespace ax::ui;

Scene* WorldScene::create()
{
    auto scene = new (std::nothrow) WorldScene();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    AX_SAFE_DELETE(scene);
    return nullptr;
}

bool WorldScene::init()
{
    if (!Scene::initWithPhysics())
        return false;
    getPhysicsWorld()->setDebugDrawMask(0xffff);
    getPhysicsWorld()->setGravity(ax::Vec2(0, -900));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();

    // Add background
    auto background = Sprite::createWithSpriteFrameName("background_day.png");
    // position the background on the center of the screen
    //    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setPosition(Vec2::ZERO);
    background->setTag(111);
    // add the background as a child to this layer
    addChild(background, 0);

    this->_background = background;

    /*
     * A node hold game world other than background
     * so that shake can work on this
     */
    _gameNode = Node::create();
    addChild(_gameNode);

    // Add ground
    _ground[0] = Sprite::createWithSpriteFrameName("ground.png");
    _ground[1] = Sprite::createWithSpriteFrameName("ground.png");

    _ground[0]->setAnchorPoint(Point::ZERO);
    _ground[1]->setAnchorPoint(Point::ZERO);

    auto boundingBox             = background->getBoundingBox();
    this->_backgroundBoundingBox = boundingBox;

    float minX = boundingBox.getMinX();
    float maxX = boundingBox.getMaxX();
    float minY = boundingBox.getMinY();
    float maxY = boundingBox.getMaxY();

    //    _ground[0]->setPosition(Point::ZERO);
    //    _ground[1]->setPosition(Vec2(_ground[0]->getContentSize().width, 0));

    _ground[0]->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0), AtaMath::interpolate(minY, maxY, 0)));
    _ground[1]->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0) + _ground[0]->getContentSize().width,
                                 AtaMath::interpolate(minY, maxY, 0)));

    _gameNode->addChild(_ground[0], 1);
    _gameNode->addChild(_ground[1], 1);

    _readyLabel = Sprite::createWithSpriteFrameName("label_get_ready.png");
    //    _readyLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*3.0f/4 + origin.y));
    _readyLabel->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, 0.75)));
    _gameNode->addChild(_readyLabel);

    _instruction = Sprite::createWithSpriteFrameName("instructions.png");
    //    _instruction->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    _instruction->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, 0.65)));
    _gameNode->addChild(_instruction);

    addPipes();
    addBird();

    _score = Score::create();
    _gameNode->addChild(_score);

    /*
     * Physics for ground, setAcnchor for node does not work
     */
    auto node        = Node::create();
    int groundHeight = _ground[0]->getContentSize().height;
    // auto edgeSegment = PhysicsShapeEdgeSegment::create(Vec2(0, groundHeight), Vec2(visibleSize.width, groundHeight));
    auto shape = PhysicsShapeBox::create(Size(visibleSize.width, groundHeight));
    auto body  = createBody(shape, false, false, GROUND_BIT, BIRD_BIT, BIRD_BIT);

    node->setPhysicsBody(body);
    //    node->setPosition(Vec2(visibleSize.width/2, groundHeight/2));
    node->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0), AtaMath::interpolate(minY, maxY, 0.1)));
    _gameNode->addChild(node);

    // Schedule update to be called per frame
    scheduleUpdate();

    // Schedule a custom update function with a specific interval
    this->schedule(AX_SCHEDULE_SELECTOR(WorldScene::update2));  // Calls customUpdate every 1 second

    _state = GameState::INIT;

    _touchOneByOneListenr = EventListenerTouchOneByOne::create();
    _touchOneByOneListenr->setSwallowTouches(false);
    _touchOneByOneListenr->onTouchBegan = AX_CALLBACK_2(WorldScene::onTouchBegan, this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchOneByOneListenr, this);
    auto contactListener            = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = AX_CALLBACK_1(WorldScene::onPhysicsContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto eventListener = EventListenerCustom::create("game_restart", [=](EventCustom* event) { restartGame(); });
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    initKeyboardListener();
    initGamepadListener();
    return true;
}

void WorldScene::initGamepadListener()
{
    auto gameControllerListener = EventListenerController::create();

    gameControllerListener->onConnected    = AX_CALLBACK_2(WorldScene::onConnectController, this);
    gameControllerListener->onDisconnected = AX_CALLBACK_2(WorldScene::onDisconnectedController, this);
    gameControllerListener->onKeyDown      = AX_CALLBACK_3(WorldScene::gamepadOnKeyDown, this);
    gameControllerListener->onKeyUp        = AX_CALLBACK_3(WorldScene::gamepadOnKeyUp, this);
    // gameControllerListener->onAxisEvent = AX_CALLBACK_3(UINavMenu::onAxisEvent, this);//Not used

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(gameControllerListener, this);
    Controller::startDiscoveryController();
}

void WorldScene::gamepadOnKeyDown(ax::Controller* controller, int keyCode, ax::Event* event)
{
    switch (keyCode)
    {
    case Controller::Key::BUTTON_DPAD_CENTER:
        HandleInput();
        break;
    case Controller::Key::BUTTON_A:
        HandleInput();
        break;
    default:
        break;
    }
}

void WorldScene::gamepadOnKeyUp(ax::Controller* controller, int keyCode, ax::Event* event) {}

void WorldScene::initKeyboardListener()
{
    keyboardListener                = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed  = AX_CALLBACK_2(WorldScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = AX_CALLBACK_2(WorldScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void WorldScene::addPipes()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int x            = visibleSize.width + PIPE_HORIZONTAL_GAP;

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        _pipes[i] = Pipes::create();
        _pipes[i]->setWorldPosition(Vec2(x, getRandomPipeY()));

        /*
         * Tag to identify the pipe so we can disable it in physics whenever needed.
         */
        _pipes[i]->setTag(i);

        _gameNode->addChild(_pipes[i]);
        x = x + _pipes[i]->getTopPipe()->getContentSize().width + PIPE_HORIZONTAL_GAP;
    }
}

void WorldScene::addBird()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();

    _bird = Bird::create();

    auto shape = PhysicsShapeCircle::create(BIRD_RADIUS);
    _bird->setPhysicsBody(createBody(shape, true, false, BIRD_BIT, GROUND_BIT | PIPE_BIT | COIN_BIT, GROUND_BIT));
    //    _bird->setPosition(Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height/2 + origin.y));

    float minX = _backgroundBoundingBox.getMinX();
    float maxX = _backgroundBoundingBox.getMaxX();
    float minY = _backgroundBoundingBox.getMinX();
    float maxY = _backgroundBoundingBox.getMaxY();

    _bird->setWorldPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.40), AtaMath::interpolate(minY, maxY, 0.5)));
    _bird->idle();

    _gameNode->addChild(_bird);
}

int WorldScene::getRandomPipeY()
{
    /// OK This one is hard
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int groundHeight = _ground[0]->getContentSize().height;

    //    int startY = _backgroundBoundingBox->getMinY()+ groundHeight + PIPE_VERTICAL_GAP/2.0f + PIPE_BOTTOM_MARGIN;
    //    int endY = visibleSize.height - PIPE_VERTICAL_GAP/2.0f - PIPE_TOP_MARGIN;
    //    int endY = _backgroundBoundingBox->getMaxY() - PIPE_VERTICAL_GAP/2.0f - PIPE_TOP_MARGIN;

    int minY = _backgroundBoundingBox.getMinY();
    int maxY = _backgroundBoundingBox.getMaxY();

    int startY = AtaMath::interpolate(minY, maxY, 0.25);
    int endY   = AtaMath::interpolate(minY, maxY, 0.75);

    return ax::RandomHelper::random_int(startY, endY);
}

bool WorldScene::onTouchBegan(Touch* touch, Event* event)
{
    HandleInput();
    return true;
}

void WorldScene::HandleInput()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    switch (_state)
    {
    case GameState::INIT:
        _state = GameState::RUNNING;
        _bird->getPhysicsBody()->setEnabled(true);
        _bird->getPhysicsBody()->setGravityEnable(true);
        _instruction->setVisible(false);
        _readyLabel->setVisible(false);
        _score->reset();
    case GameState::RUNNING:
        // SimpleAudioEngine::getInstance()->playEffect("sfx_wing.wav");//TODO Upgrade the Audio
        AudioEngine::play2d("sfx_wing.wav");
        _bird->fly();

        /*
         * Dont let bird fly beyond a height otherwise bird could fly above the pipes
         */
        if (_bird->getPositionY() < visibleSize.height + 70)
            _bird->getPhysicsBody()->setVelocity(Vec2(0, 300));

        _bird->getPhysicsBody()->setAngularVelocity(3);
        break;
    }
}

/*
 * Returning false from this callback let ignore this collision by the physics world
 * or return true to process it normally
 */
bool WorldScene::onPhysicsContactBegin(const PhysicsContact& contact)
{
#if BIRD_BODY_NOT_REMOVED_FROM_WORLD
    if (_state == GameState::OVER)
    {
        /*
         * If we don't return true from here physics body ignore the collision
         * which may result in bird passing though the ground even after onGameOver
         * best solution would be to remove the physics body.
         *
         * Even with this bird has interaction with grond even after onGameOver, so we disable bird
         * physics body once we are in gameover state.
         */
        return true;
    }
#endif

    PhysicsBody* birdBody  = contact.getShapeA()->getBody();
    PhysicsBody* otherBody = contact.getShapeB()->getBody();

    if (birdBody->getCategoryBitmask() != BIRD_BIT)
    {
        std::swap(birdBody, otherBody);
    }

    if (otherBody->getCategoryBitmask() == COIN_BIT)
    {
        // SimpleAudioEngine::getInstance()->playEffect("sfx_point.wav");
        AudioEngine::play2d("sfx_point.wav");

        _score->addScore();

        /*
         * Disable this body so same coin cannot be collected again.
         */
        otherBody->setEnabled(false);

        /*
         * We dont want this collision to be processed by world, as we just need to add up to the coin.
         */
        return false;
    }

    auto body = _bird->getPhysicsBody();
    if (otherBody->getCategoryBitmask() == PIPE_BIT)
    {
        body->setAngularVelocity(-1.5);  // Let it fall to ground with some angular velocity
        if (_state != GameState::HIT)
        {
            doShake();
            // SimpleAudioEngine::getInstance()->playEffect("sfx_hit.wav");
            AudioEngine::play2d("sfx_hit.wav");
        }
        _state = GameState::HIT;

        /*
         * Disable physics for this pipe so it wont create more contact callbacks
         */
        int tag = otherBody->getTag();
        if (tag >= 0 && tag < PIPE_COUNT)
        {
            _pipes[tag]->setPhysicsEnabled(false);
        }
    }
    else
    {
        body->setAngularVelocity(0);    // Bird hit the ground set angular velocity to 0
        body->setVelocity(Vec2::ZERO);  // Bird hit the gorund set zero velocity
        _state = GameState::OVER;

        /*
         * Game is over, disable physics simulaiton for this bird
         */
        body->setEnabled(false);
    }

    _bird->stop();

    return true;
}

void WorldScene::update2(float dt)
{
    auto camera = Camera::getDefaultCamera();
    camera->setWorldPosition(Vec2::ZERO);

    Size visibleSize        = Director::getInstance()->getVisibleSize();
    float boundingBoxHeight = _backgroundBoundingBox.size.height;

    bool isLandscape = (visibleSize.width / visibleSize.height) > 1;
    // Calculate the desired zoom factor
    float desiredHeight = isLandscape ? visibleSize.height * 0.5 : visibleSize.width * 0.35;
    float zoomFactor    = desiredHeight / boundingBoxHeight;

    camera->setZoom(zoomFactor);
}

void WorldScene::update(float dt)
{
    if (_state == GameState::OVER)
    {
        if (_bird->getRotation() > 30)
        {
            _bird->setRotation(30);
        }
        onGameOver();
        unscheduleUpdate();

        return;
    }

    if (_state != GameState::RUNNING && _state != GameState::INIT)
        return;

    float groundWidth = _ground[0]->getContentSize().width;
    for (int i = 0; i < 2; i++)
    {
        _ground[i]->setPositionX(_ground[i]->getPositionX() - 2.0f);
        if (_ground[i]->getPositionX() < -groundWidth)
        {
            _ground[i]->setPositionX(_ground[i]->getPositionX() + 2 * groundWidth);
        }
    }

    if (_state != GameState::RUNNING)
        return;

    auto body = _bird->getPhysicsBody();
    if (body)
    {
        if (_bird->getRotation() < -30)
        {
            body->setAngularVelocity(0);
            _bird->setRotation(-30);
        }

        if (body->getVelocity().y < 0)
        {
            body->setAngularVelocity(-1.5);
            _bird->stop();
        }
    }

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        _pipes[i]->setPositionX(_pipes[i]->getPositionX() - 2.0f);

        if (_pipes[i]->getPositionX() < -_pipes[i]->getTopPipe()->getContentSize().width - 3)
        {
            _pipes[i]->setPosition(
                Vec2(_pipes[i]->getPositionX() +
                         PIPE_COUNT * (_pipes[i]->getTopPipe()->getContentSize().width + PIPE_HORIZONTAL_GAP),
                     getRandomPipeY()));
            _pipes[i]->setCoinPhysicsEnabled(true);
        }
    }
}

void WorldScene::onGameOver()
{
    _score->setVisible(false);
    _instruction->setVisible(false);
    _readyLabel->setVisible(false);
    doShake();

    // SimpleAudioEngine::getInstance()->playEffect("sfx_die.wav");
    AudioEngine::play2d("sfx_die.wav");
    auto gameOver = GameOver::create(_score->getScore());
    addChild(gameOver, 1);
}

void WorldScene::restartGame()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();
    int x            = visibleSize.width + PIPE_HORIZONTAL_GAP;

    float minX = _backgroundBoundingBox.getMinX();
    float maxX = _backgroundBoundingBox.getMaxX();
    float minY = _backgroundBoundingBox.getMinX();
    float maxY = _backgroundBoundingBox.getMaxY();

    _bird->setWorldPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.40), AtaMath::interpolate(minY, maxY, 0.5)));
    //    _bird->setPosition(Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height/2 + origin.y));

    _bird->getPhysicsBody()->setGravityEnable(false);
    _bird->getPhysicsBody()->setVelocity(Vec2::ZERO);
    _bird->setRotation(0);
    _bird->idle();

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        _pipes[i]->setPosition(Vec2(x, getRandomPipeY()));
        x = x + _pipes[i]->getTopPipe()->getContentSize().width + PIPE_HORIZONTAL_GAP;
        _pipes[i]->setPhysicsEnabled(true);
    }

    _score->reset();
    _score->setVisible(true);
    _instruction->setVisible(true);
    _readyLabel->setVisible(true);
    _state = GameState::INIT;

    scheduleUpdate();
}

void WorldScene::doShake()
{
    stopAllActions();
    _gameNode->runAction(Shake::create(.2f, Vec2(3, 3)));
}

void WorldScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case ax::EventKeyboard::KeyCode::KEY_BACKSPACE:
        HandleInput();
        break;
    default:
        break;
    }
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode, Event* event) {}

void WorldScene::onConnectController(Controller* controller, Event* event) {}

void WorldScene::onDisconnectedController(Controller* controller, Event* event) {}
