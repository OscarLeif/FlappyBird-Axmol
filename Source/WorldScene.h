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
#include "UINavMenu.h"
#include "base/GameController.h"


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
    void update2(float dt);
    static WorldScene Get;
    Rect _backgroundBoundingBox;
    UINavMenu* UINavMenu;
    EventListenerKeyboard* keyboardListener;

    void initGamepadListener();
    void initKeyboardListener();

private:
    void addPipes();
    void addBird();
    int getRandomPipeY();
    bool onTouchBegan(Touch* touch, Event* event);
    void HandleInput();
    bool onPhysicsContactBegin(const PhysicsContact& contact);
    void onGameOver();
    void restartGame();
    void doShake();
    // keyboard
    void onKeyPressed(EventKeyboard::KeyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode, Event* event);
    // Gamepad controller listener
    void onConnectController(Controller* controller, Event* event);
    void onDisconnectedController(Controller* controller, Event* event);
    void gamepadOnKeyDown(ax::Controller* controller, int keyCode, ax::Event* event);
    void gamepadOnKeyUp(ax::Controller* controller, int keyCode, ax::Event* event);

private:
    Sprite* _ground[2];
    Sprite* _instruction;
    Sprite* _readyLabel;
    Sprite* _background;

    Score* _score;
    Bird* _bird;
    Pipes* _pipes[PIPE_COUNT];
    GameState _state;
    Node* _gameNode;
    EventListenerTouchOneByOne* _touchOneByOneListenr;

    // Keyboard
};

#endif  // FLAPPYBIRD_WORLDSCENE_H
