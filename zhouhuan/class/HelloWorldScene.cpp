#include "HelloWorldScene.h"
#include "D:\projects\hellotest\proj.win32\GameScene.h"

USING_NS_CC;

GameScene  *scene1=NULL;

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
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
   auto touchtostart = MenuItemImage::create(
                                           "txt_touchtostart.png",
										   "txt_touchtostart.png",
										 
                                           //"CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menustartCallback, this));


	touchtostart->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-35));


    // create menu, it's an autorelease object
    auto menu = Menu::create(touchtostart,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    /*auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);*/

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("bg_title.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 1);


	  sprite = Sprite::create("txt_title.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+60));

    // add the sprite as a child to this layer
    this->addChild(sprite, 1);

	/*sprite = Sprite::create("txt_touchtostart.png");

    // position the sprite on the center of the screen
   sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-35));

    // add the sprite as a child to this layer
    this->addChild(sprite, 2);*/

    scene1 = GameScene::create ();
	this->addChild (scene1);
    return true;
}


/*void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}*/

void HelloWorld::menustartCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

//	auto scene=GameScene::createScene();
    Director::getInstance()->replaceScene(scene1);
	//scene1  = GameScene::createScene(); 
	//this->addChild (scene1,1 );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)



    exit(0);
#endif
}

