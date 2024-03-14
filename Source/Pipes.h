//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_PIPES_H
#define FLAPPYBIRD_PIPES_H

#include "axmol.h"

USING_NS_AX;

class Pipes: public Node
{
public:
    static Pipes* create();
    virtual bool init();
    Sprite* getTopPipe(){return _top;}
    Sprite* getBottomPipe(){return _bottom;}
    void setCoinPhysicsEnabled(bool enable);
    void setPhysicsEnabled(bool enable);
    void setTag(int tag);
private:
    Sprite* _top;
    Sprite* _bottom;
    PhysicsBody* _coin;
};
#endif //FLAPPYBIRD_PIPES_H
