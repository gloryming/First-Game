#pragma once
#include "AppDelegate.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "OperationLayer.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
	//auto eglView = GLView ::getInstance();
	//director->setOpenGLView(eglView);
    //eglView->setDesignResolutionSize(480, 320, ResolutionPolicy::SHOW_ALL);
   if(!glView){
        glView = GLView::create("My Game");
        director->setOpenGLView(glView);
	//ÎÒ×¢ÊÍµôµÄ	glView->setDesignResolutionSize(480, 320, ResolutionPolicy::SHOW_ALL);
    }
   auto Size = director->getWinSize();

   glView->setFrameSize(854, 480);
   glView->setDesignResolutionSize(480.0f, 320.0f, ResolutionPolicy::FIXED_HEIGHT);

   std::vector<std::string> searchPath;
   searchPath.push_back("Hero");
   searchPath.push_back("Sprites");
   CCFileUtils::getInstance()->setSearchPaths(searchPath);

   srand(time(NULL));

    // turn on display FPS
	director->setDisplayStats(true);
    //director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainScene::create();
    
	//run
    director->runWithScene(scene);
	
	

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
