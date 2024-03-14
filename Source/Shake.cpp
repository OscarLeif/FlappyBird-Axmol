//
// Created by oscar on 3/13/2024.
//

#include "Shake.h"

Shake* Shake::create(float duration, float magnitude)
{
    return create(duration, Vec2(magnitude, magnitude));
}

Shake* Shake::create(float duration, Vec2 magnitude)
{
    Shake* action = new Shake();
    if (action && action->initWithDuration(duration, magnitude)) {
        action->autorelease();
        return action;
    }
    AX_SAFE_DELETE(action);
    return nullptr;
}

Shake* Shake::clone() const
{
    return create(_duration, _magnitude);
}

Shake* Shake::reverse() const
{
    return create(_duration, -_magnitude);
}

void Shake::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _initial = target->getPosition();
}

void Shake::update(float time)
{
    Vec2 offset(RandomHelper::random_real(-_magnitude.x, _magnitude.x),
                RandomHelper::random_real(-_magnitude.y, _magnitude.y));
    _target->setPosition(_initial + offset);
}

void Shake::stop(void)
{
    _target->setPosition(_initial);
    ActionInterval::stop();

}

bool Shake::initWithDuration(float duration, axmol::Vec2 magnitude)
{
    if (ActionInterval::initWithDuration(duration)) {
        _magnitude = magnitude;
        return true;
    }
    return false;
}
