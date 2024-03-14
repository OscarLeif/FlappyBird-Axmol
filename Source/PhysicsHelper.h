//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_PHYSICSHELPER_H
#define FLAPPYBIRD_PHYSICSHELPER_H

#include "axmol.h"

USING_NS_AX;


PhysicsBody* createBody(PhysicsShape* shape, bool dynamic, bool enableGravity, int categoryMask, int contactTestMask, int collisionMask);



#endif //FLAPPYBIRD_PHYSICSHELPER_H
