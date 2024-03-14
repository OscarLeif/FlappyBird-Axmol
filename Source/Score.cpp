//
// Created by oscar on 3/13/2024.
//

#include "Score.h"

Score* Score::create()
{
    Score* score = new (std::nothrow) Score();
    if (score && score->init())
    {
        score->autorelease();
        return score;
    }
    AX_SAFE_DELETE(score);
    return nullptr;
}

bool Score::init()
{
    if (!Node::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _score = 0;

    _scoreLabel = Label::createWithBMFont("font.fnt", "0");
    _scoreLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.92f + origin.y));
    addChild(_scoreLabel);
    return true;
}

void Score::addScore()
{
    _score++;
    char score[12];
    sprintf(score, "%d", _score);
    _scoreLabel->setString(score);
}

void Score::reset()
{
    _score = 0;
    _scoreLabel->setString("0");
}

int Score::getScore()
{
    return _score;
}

void Score::updateScore()
{
    int topScore = UserDefault::getInstance()->getIntegerForKey("topScore", -1);
    if (topScore < _score) {
        UserDefault::getInstance()->setIntegerForKey("topScore", _score);
        UserDefault::getInstance()->flush();
    }
}

int Score::getTopScore()
{
    return UserDefault::getInstance()->getIntegerForKey("topScore", 0);
}

//Score::Score() { }
//Score::~Score() { }
