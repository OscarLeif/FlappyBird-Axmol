//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_GAMEOVER_H
#define FLAPPYBIRD_GAMEOVER_H


#include "axmol.h"
#include "ui/axmol-ui.h"

#include "WorldScene.h"

USING_NS_AX;
using namespace axmol::ui;

class GameOver: public Node
{
public:
    static GameOver* create(int score);
    virtual bool init(int score);
    /*AX_CONSTRUCTOR_ACCESS:
    GameOver();
    ~GameOver();*/

private:
    void onAnimationFinished();
    void randomizeSparkle();
    void scoreCounter(float dt);

private:
    BetterButton* _playButton;
    BetterButton* _scoreButton;
    Sprite* _sparkle;
    Label* _bestScoreLabel;
    Label* _scoreLabel;
    int _score;
    int _topScore;
    int _count;
public:
    WorldScene* worldScene;
};

#endif //FLAPPYBIRD_GAMEOVER_H
