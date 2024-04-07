//
// Created by oscar on 3/13/2024.
//

#include "GameOver.h"
#include "audio/AudioEngine.h"
#include "AtaMath.h"
#include "UINavMenu.h"

using namespace axmol::ui;
// using namespace CocosDenshion;

GameOver* GameOver::create(int score)
{
    GameOver* gameOver = new (std::nothrow) GameOver();
    if (gameOver && gameOver->init(score))
    {
        gameOver->autorelease();
        return gameOver;
    }
    AX_SAFE_DELETE(gameOver);
    return nullptr;
}

bool GameOver::init(int score)
{
    if (!Node::init())
        return false;

    _score = score;
    _count = 0;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();

    // game over label image
    auto gameOverLabel = Sprite::createWithSpriteFrameName("label_game_over.png");
    gameOverLabel->setOpacity(0);

    // missing reference
    auto scene      = Director::getInstance()->getRunningScene();
    auto worldScene = scene->getChildByTag(111);

    Rect bounds = Rect();

    if (worldScene)
    {
        // WorldScene found, you can use it here
        auto a = dynamic_cast<Sprite*>(worldScene);
        bounds = a->getBoundingBox();
    }
    else
    {
        // WorldScene not found
    }

    auto b = bounds;

    float minX = b.getMinX();
    float maxX = b.getMaxX();
    float minY = b.getMinY();
    float maxY = b.getMaxY();

    //    gameOverLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*5.0/6 + origin.y));
    float a = AtaMath::interpolate(minY, maxY, 0.75);
    gameOverLabel->setWorldPosition(
        Vec2(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, 0.80)));

    FadeIn* fadeIn = FadeIn::create(0.3f);
    gameOverLabel->runAction(fadeIn);

    addChild(gameOverLabel, 2);

    _playButton =
        BetterButton::create("button_play_normal.png", "button_play_pressed.png", "", Widget::TextureResType::PLIST);
    _playButton->setVisible(false);
    //    _playButton->setPosition(Vec2(visibleSize.width/2 - _playButton->getContentSize().width/2 - 8 + origin.x,
    //    visibleSize.height/3 + origin.y));
    _playButton->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.25), AtaMath::interpolate(minY, maxY, 0.35)));
    _playButton->addClickEventListener([=](Ref* sender) {
        // SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.wav");
        AudioEngine::play2d("sfx_swooshing.wav");
        EventCustom event("game_restart");
        getEventDispatcher()->dispatchEvent(&event);
        this->removeFromParentAndCleanup(true);
    });
    addChild(_playButton, 2);

    _scoreButton =
        BetterButton::create("button_score_normal.png", "button_score_pressed.png", "", Widget::TextureResType::PLIST);
    _scoreButton->setVisible(false);
    //    _scoreButton->setPosition(Vec2(visibleSize.width/2 + _playButton->getContentSize().width/2 + 8 + origin.x,
    //    visibleSize.height/3 + origin.y));
    _scoreButton->setPosition(Vec2(AtaMath::interpolate(minX, maxX, 0.75), AtaMath::interpolate(minY, maxY, 0.35)));

    addChild(_scoreButton, 2);

    _playButton->righButton  = _scoreButton;
    _scoreButton->leftButton = _playButton;

    auto scorePanel = Sprite::createWithSpriteFrameName("panel_score.png");
    // Vec2 endPos(visibleSize.width/2 + origin.x, visibleSize.height*3.5/6 + origin.y);
    // Vec2 startPos(visibleSize.width/2 + origin.x, -scorePanel->getContentSize().height/2 + origin.y);
    Vec2 endPos(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, 0.60));
    Vec2 startPos(AtaMath::interpolate(minX, maxX, 0.5), AtaMath::interpolate(minY, maxY, 0.65) - visibleSize.y);
    auto moveTo             = MoveTo::create(0.5f, endPos);
    UINavMenu::readingInput = false;
    auto actionDone         = CallFunc::create(AX_CALLBACK_0(GameOver::onAnimationFinished, this));
    auto seq                = Sequence::createWithTwoActions(EaseExponentialOut::create(moveTo), actionDone);
    scorePanel->runAction(seq);
    scorePanel->setPosition(startPos);

    addChild(scorePanel, 2);

    char scoreStr[32];
    sprintf(scoreStr, "%d", _score);
    _scoreLabel = Label::createWithBMFont("scoreFont.fnt", "0");
    _scoreLabel->setPosition(Vec2(180, 66));
    _scoreLabel->setVisible(false);
    scorePanel->addChild(_scoreLabel, 2);

    _topScore = UserDefault::getInstance()->getIntegerForKey("topScore", 0);
    sprintf(scoreStr, "%d", _topScore);

    _bestScoreLabel = Label::createWithBMFont("scoreFont.fnt", scoreStr);
    _bestScoreLabel->setPosition(182, 24);
    scorePanel->addChild(_bestScoreLabel, 2);

    const char* medalSprite = nullptr;

    if (_score >= 10)
        medalSprite = "medal_bronze.png";
    if (_score >= 20)
        medalSprite = "medal_silver.png";
    if (_score >= 30)
        medalSprite = "medal_gold.png";
    if (_score >= 40)
        medalSprite = "medal_platinum.png";

    auto navMenu = UINavMenu::create();
    addChild(navMenu);

    navMenu->setSelectedButton(_playButton);
    navMenu->initKeyboardListener();
    navMenu->RegisterControllerListener();

    if (medalSprite)
    {
        auto medal = Sprite::createWithSpriteFrameName(medalSprite);
        medal->setPosition(Vec2(48, 48));
        scorePanel->addChild(medal, 2);

        auto spritecache = SpriteFrameCache::getInstance();
        char spark[32];
        Vector<SpriteFrame*> animFrames(3);
        for (int i = 0; i < 3; i++)
        {
            sprintf(spark, "spark_%d.png", i);
            auto frame = spritecache->getSpriteFrameByName(spark);
            animFrames.pushBack(frame);
        }

        _sparkle = Sprite::createWithSpriteFrame(animFrames.front());

        auto sparkleAnim = Animation::createWithSpriteFrames(animFrames, 1.0f / 5);
        auto shine       = RepeatForever::create(Sequence::create(
            CallFunc::create(AX_CALLBACK_0(GameOver::randomizeSparkle, this)), Animate::create(sparkleAnim), nullptr));

        _sparkle->runAction(shine);
        scorePanel->addChild(_sparkle, 2);
    }
    return true;
}

void GameOver::scoreCounter(float dt)
{
    char scoreStr[32];
    sprintf(scoreStr, "%d", _count);
    _scoreLabel->setString(scoreStr);

    if (_count == _score)
    {
        if (_score > _topScore)
        {
            char scoreStr[32];
            sprintf(scoreStr, "%d", _score);
            _bestScoreLabel->setString(scoreStr);
        }
        unschedule("score_counter");
    }

    _count++;
    UINavMenu::readingInput = true;
}

void GameOver::onAnimationFinished()
{
    _scoreButton->setVisible(true);
    _playButton->setVisible(true);
    _scoreLabel->setVisible(true);

    if (_topScore < _score)
    {
        UserDefault::getInstance()->setIntegerForKey("topScore", _score);
        UserDefault::getInstance()->flush();

        char scoreStr[32];
        sprintf(scoreStr, "%d", _topScore);
        _bestScoreLabel->setString(scoreStr);
    }

    schedule(AX_CALLBACK_1(GameOver::scoreCounter, this), 0.1f, "score_counter");
}

void GameOver::randomizeSparkle()
{
    int angle  = axmol::RandomHelper::random_int(0, 360);
    int radius = axmol::RandomHelper::random_int(0, 22);
    _sparkle->setPosition(Vec2(radius * sin(angle) + 48, radius * cos(angle) + 48));
}

// GameOver::GameOver() { }
// GameOver::~GameOver() { }
