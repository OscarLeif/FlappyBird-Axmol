//
// Created by oscar on 06/03/2026.
//

#include "MainMenu.h"

#include "Inspector/Inspector.h"
//#include "OrbitCameraController.h"

using namespace ax;

bool MainMenu::init()
{

    if (!Scene::init())
    {
        return false;
    }
    auto defaultCamera = getDefaultCamera();
    defaultCamera->setPosition3D(Vec3(0,0,500));
    defaultCamera->setVisible(false);
    //camera->lookAt(Vec3(0,0,0));
    //camera->setWorldPosition(Vec2::ZERO);

    auto background = Sprite::createWithSpriteFrameName("background_day.png");
    background->setPosition3D(Vec3::ZERO);
    addChild(background);

    extension::Inspector::getInstance()->openForScene(this);

    /*auto camera3D= Camera::create();
    camera3D->setPosition3D(Vec3::ZERO);
    addChild(camera3D);*/

    auto frameSize = Director::getInstance()->getRenderView()->getFrameSize();
    float aspect   = frameSize.width / frameSize.height;

    // Get aspect ratio
    auto frameSize = Director::getInstance()->getRenderView()->getFrameSize();
    float aspect   = frameSize.width / frameSize.height;

    // Create perspective camera
    auto camera = Camera::createPerspective(60.0f, aspect, 1.0f, 1000.0f);
    camera->setCameraFlag(CameraFlag::DEFAULT);
    addChild(camera);

    // Attach orbit controller to camera
    auto orbit = OrbitCameraController::create(camera);
    orbit->setTarget(Vec3::ZERO);
    orbit->setDistance(500.0f);
    orbit->setPitch(20.0f);
    addChild(orbit);


    


    //scheduleUpdate();
    return true;
}

void MainMenu::update(float dt) {
    if(frameCounter==0)
    {
        _defaultCamera->setPosition3D(Vec3::ZERO);
    }
    frameCounter++;
}

MainMenu::MainMenu() {

}

MainMenu::~MainMenu() {

}




