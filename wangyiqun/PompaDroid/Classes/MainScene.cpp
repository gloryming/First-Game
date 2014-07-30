#include "MainScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 
	auto startPushButton = MenuItemImage::create("txt_touchtostart.png", "txt_touchtostart.png", [&](Ref* sender){
		{	log("selected");
		Director::getInstance()->setContentScaleFactor(320.0/320.0f);
		auto transitions = TransitionFade::create(0.3f, GameScene::createScene());
		Director::getInstance()->replaceScene(transitions);
		}
	});
	startPushButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 * 0.8 + origin.y));
	
	//
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
	menu->addChild(startPushButton);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//add  "txt_title"
	auto title = Sprite::create("txt_title.png");
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 * 1.35 + origin.y));
	this->addChild(title, 5);

    // add "bg_title"
    auto sprite = Sprite::create("bg_title.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
