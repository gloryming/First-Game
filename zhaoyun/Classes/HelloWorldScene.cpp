#include "HelloWorldScene.h"

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

bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();


   auto touchtostart = MenuItemImage::create(
                                           "txt_touchtostart.png",
										   "txt_touchtostart.png",
										 
                                           CC_CALLBACK_1(HelloWorld::menustartCallback, this));


	touchtostart->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-35));


    auto menu = Menu::create(touchtostart,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);


    auto sprite = Sprite::create("bg_title.png");

    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 1);


	  sprite = Sprite::create("txt_title.png");

    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+60));


    this->addChild(sprite, 1);


	scene1  = GameScene::create(); 
	this->addChild (scene1);
    
    return true;
}




void HelloWorld::menustartCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

	
    Director::getInstance()->replaceScene(scene1);
	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

