//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_SHAKE_H
#define FLAPPYBIRD_SHAKE_H

#include "axmol.h"

USING_NS_AX;

class Shake : public ActionInterval
{
public:
    /*
     * Create a shake action with duration and magnitude
     */
    static Shake* create(float duration, float magnitude);
    static Shake* create(float duration, Vec2 magnitude);

    /*
     * Overrides
     */
    virtual Shake* clone() const override;
    virtual Shake* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual void stop(void) override;

    bool initWithDuration(float duration, ax::Vec2 magnitude);


    Shake() { }
    virtual ~Shake() { }

private:
    AX_DISALLOW_COPY_AND_ASSIGN(Shake);

private:
    Vec2 _magnitude;
    Vec2 _initial;
};


#endif //FLAPPYBIRD_SHAKE_H
