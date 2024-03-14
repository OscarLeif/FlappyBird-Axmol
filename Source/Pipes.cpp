//
// Created by oscar on 3/13/2024.
//

#include "Pipes.h"
#include "Settings.h"
#include "PhysicsHelper.h"

Pipes* Pipes::create()
{
    Pipes* pipes = new (std::nothrow) Pipes();
    if (pipes && pipes->init())
    {
        pipes->autorelease();
        return pipes;
    }
    AX_SAFE_DELETE(pipes);
    return nullptr;
}

bool Pipes::init()
{
    if (!Node::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _top = Sprite::createWithSpriteFrameName("pipe_green_top.png");

    auto shape = PhysicsShapeBox::create(_top->getContentSize());

    _top->setPhysicsBody(createBody(shape, false, false, PIPE_BIT, BIRD_BIT, BIRD_BIT));
    _top->setPosition(Vec2(0, _top->getContentSize().height/2.0f +  PIPE_VERTICAL_GAP/2.0f));

    _bottom = Sprite::createWithSpriteFrameName("pipe_green_bottom.png");

    shape = PhysicsShapeBox::create(_bottom->getContentSize());

    _bottom->setPhysicsBody(createBody(shape, false, false, PIPE_BIT, BIRD_BIT, BIRD_BIT));
    _bottom->setPosition(Vec2(0, -_bottom->getContentSize().height/2.0f - PIPE_VERTICAL_GAP/2.0f));

    // add these sprite as a child to this layer
    addChild(_top, 0);
    addChild(_bottom, 0);

    //Add physics body to detect if bird has crossed the pipe and add score
    auto node = Node::create();

    auto edgeSegment = PhysicsShapeEdgeSegment::create(Vec2(0, PIPE_VERTICAL_GAP/2.0f), Vec2(0, -PIPE_VERTICAL_GAP/2.0f));
    _coin = createBody(edgeSegment, false, false, COIN_BIT, BIRD_BIT, BIRD_BIT);

    node->setPhysicsBody(_coin);

    addChild(node);

    return true;
}

/*
 * Set whether physics for coin colleciton is enabled, this is neccesory to
 * disable it once a coin is collected otherwise same coin can be collected
 * multiple time due to physics bounces.
 */
void Pipes::setCoinPhysicsEnabled(bool enable)
{
    _coin->setEnabled(enable);
}

void Pipes::setPhysicsEnabled(bool enable)
{
    _top->getPhysicsBody()->setEnabled(enable);
    _bottom->getPhysicsBody()->setEnabled(enable);
    _coin->setEnabled(enable);
}

void Pipes::setTag(int tag)
{
    _top->getPhysicsBody()->setTag(tag);
    _bottom->getPhysicsBody()->setTag(tag);
}
