//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_SCORE_H
#define FLAPPYBIRD_SCORE_H


#include "axmol.h"

USING_NS_AX;

class Score: public Node
{
public:
    static Score* create();
    virtual bool init();
    void addScore();
    int getScore();
    void reset();
    void updateScore();
    int getTopScore();
    //CC_CONSTRUCTOR_ACCESS:
    //        Score();
    ~Score();
private:
    int _score;
    Label* _scoreLabel;
};


#endif //FLAPPYBIRD_SCORE_H
