/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "MainScene.h"
#include "WelcomeScene.h"

#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#    include "audio/AudioEngine.h"
#endif

using namespace ax;

#include "Inspector/Inspector.h"
#if AX_ENABLE_EXT_IMGUI

#endif

static ax::Size designResolutionSize = ax::Size(720, 1280);//default (1280,720)

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

// if you want a different context, modify the value of gfxContextAttrs
// it will affect all platforms
void AppDelegate::initGfxContextAttrs()
{
    // set graphics context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GfxContextAttrs gfxContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    // since axmol-2.2 vsync was enabled in engine by default
    // gfxContextAttrs.vsync = false;

    RenderView::setGfxContextAttrs(gfxContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto renderView   = director->getRenderView();
    if (!renderView)
    {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || \
    (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
        renderView = RenderViewImpl::createWithRect("FlappyBird", ax::Rect(0, 0, designResolutionSize.width, designResolutionSize.height), 1.0F, true);
        //glView = GLViewImpl::create("FlappyBird", true);  // Android means use fullscreen resolution this will not work on new versions
#else
        renderView = RenderViewImpl::createWithFullScreen("FlappyBird"); // Android means use fullscreen resolution
#endif
        director->setRenderView(renderView);
    }

    // turn on display FPS
    director->setStatsDisplay(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    auto frameSize = renderView->getFrameSize(); // Use FrameSize for physical aspect ratio
    float aspectRatio = frameSize.width / frameSize.height;

    if (aspectRatio > 1.0f) {
        // Landscape (TV)
        renderView->setDesignResolutionSize(1280, 720, ResolutionPolicy::FIXED_HEIGHT);
    } else {
        // Portrait (Phone)
        renderView->setDesignResolutionSize(720, 1280, ResolutionPolicy::FIXED_WIDTH);
    }

    auto sharedFileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;

    searchPaths.push_back("audio");
    sharedFileUtils->setSearchPaths(searchPaths);

    // create a scene. it's an autorelease object
    //auto scene = utils::createInstance<MainScene>();

    auto welcomeScene = utils::createInstance<WelcomeScene>();

    // run
    director->runWithScene(welcomeScene);


    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
void AppDelegate::applicationScreenSizeChanged(int newWidth, int newHeight)
{
    if (newWidth <= 0 || newHeight <= 0) return;

    auto director = Director::getInstance();
    auto renderView = director->getRenderView();
    if (renderView)
    {
        auto frameSize = renderView->getFrameSize(); // Use FrameSize for physical aspect ratio
        float aspectRatio = frameSize.width / frameSize.height;

        if (aspectRatio > 1.0f) {
            // Landscape (TV)
            renderView->setDesignResolutionSize(1280, 720, ResolutionPolicy::FIXED_HEIGHT);
        } else {
            // Portrait (Phone)
            renderView->setDesignResolutionSize(720, 1280, ResolutionPolicy::FIXED_WIDTH);
        }
    }
}
#endif
