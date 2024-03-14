//
// Created by oscar on 3/13/2024.
//

#ifndef FLAPPYBIRD_WORLDSCENE_H
#define FLAPPYBIRD_WORLDSCENE_H


#include "axmol.h"
#include "Settings.h"
#include "Pipes.h"
#include "Bird.h"
#include "Score.h"

USING_NS_AX;

enum GameState
{
    INIT = 0,
    RUNNING,
    HIT,
    PAUSE,
    OVER
};

class WorldScene : public ax::Scene
{
public:
    // implement the "static create()" method manually
    static ax::Scene* create();
    virtual bool init();
    virtual void update(float dt);

private:
    void addPipes();
    void addBird();
    int getRandomPipeY();
    bool onTouchBegan(Touch* touch, Event* event);
    bool onPhysicsContactBegin(const PhysicsContact &contact);
    void onGameOver();
    void restartGame();
    void doShake();

private:
    Sprite* _ground[2];
    Sprite* _instruction;
    Sprite* _readyLabel;
    Score* _score;
    Bird* _bird;
    Pipes* _pipes[PIPE_COUNT];
    GameState _state;
    Node* _gameNode;
    EventListenerTouchOneByOne * _touchOneByOneListenr;
};


#endif //FLAPPYBIRD_WORLDSCENE_H
