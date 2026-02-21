//
// Created by oscar on 3/13/2024.
//

#include "Bird.h"

int Bird::_birdId = -1;

Bird* Bird::create()
{
    Bird* bird = new (std::nothrow) Bird();
    if (bird && bird->init())
    {
        bird->autorelease();
        return bird;
    }
    AX_SAFE_DELETE(bird);
    return nullptr;
}

Bird::Bird() : _idle(nullptr), _fly(nullptr), _swing(nullptr) {}

Bird::~Bird()
{
    // Clean up retained actions to prevent memory leaks
    AX_SAFE_RELEASE(_idle);
    AX_SAFE_RELEASE(_fly);
    AX_SAFE_RELEASE(_swing);
}

bool Bird::init()
{
    auto spritecache = SpriteFrameCache::getInstance();
    const char* type[] = { "blue", "orange", "red" };

    // Pick color once
    if (_birdId == -1) {
        _birdId = ax::RandomHelper::random_int(0, 2);
    }

    // 1. Create Ping-Pong Frame Sequence (0, 1, 2, 1)
    Vector<SpriteFrame*> animFrames;
    int indices[] = {0, 1, 2, 1};
    for(int i : indices) {
        std::string name = StringUtils::format("bird_%s_%d.png", type[_birdId], i);
        auto frame = spritecache->getSpriteFrameByName(name);
        if(frame) animFrames.pushBack(frame);
    }

    if (animFrames.empty() || !initWithSpriteFrame(animFrames.front())) {
        return false;
    }

    // 2. Setup Flap Animation
    auto flapAnim = Animation::createWithSpriteFrames(animFrames, 0.1f); // 10 FPS

    // 3. Create Actions
    // Idle: Flap once, wait a bit, repeat + Swing up/down
    auto flapOnce = Animate::create(flapAnim);
    _idle = RepeatForever::create(Sequence::create(flapOnce, DelayTime::create(0.01f), nullptr));
    _idle->retain();

    // Fly: Constant flapping
    _fly = RepeatForever::create(Animate::create(flapAnim));
    _fly->retain();

    // Swing: Smooth sine-wave like movement
    auto moveUp = MoveBy::create(0.3f, Vec2(0, 6));
    auto moveDown = moveUp->reverse();
    _swing = RepeatForever::create(Sequence::create(moveUp, moveDown, nullptr));
    _swing->retain();

    return true;
}

void Bird::idle()
{
    this->stopAllActions();

    // Instead of running a stored pointer, we create a fresh one
    // or clone the existing one. Cloning is the easiest fix:
    if (_idle) {
        this->runAction(_idle->clone()); // .clone() creates a unique copy!
    }
    if (_swing) {
        this->runAction(_swing->clone());
    }
}

void Bird::fly()
{
    this->stopAllActions();
    if (_fly) {
        this->runAction(_fly->clone());
    }
}

void Bird::stop()
{
    this->stopAllActions();
}
