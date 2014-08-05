#include "PompaDroidLayer.h"
#include "GameScene.h"

USING_NS_CC;

Scene* PompaDroid::createScene()
{
    auto scene = Scene::create();
	auto layer = PompaDroid::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool PompaDroid::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size winSize = Director::getInstance()->getWinSize();

	// init background
	auto background = Sprite::create("bg_title.png");
	background->setAnchorPoint(Vec2(0, 1));
	background->setPosition(Vec2(0, winSize.height));
	this->addChild(background, -1);

    // init menu
    auto startItem = MenuItemImage::create(
                                           "txt_touchtostart.png",
                                           "txt_touchtostart.png",
										   CC_CALLBACK_1(PompaDroid::menustartCallback, this));
    
	startItem->setPosition(Vec2(winSize.width /2 ,
		winSize.height / 2 - startItem->getContentSize().height * 2));
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // init title
    
	auto title = Sprite::create("txt_title.png");
    title->setPosition(Vec2(winSize.width/2,
                            winSize.height * 2 / 3));
    this->addChild(title, 1);
	
    return true;
}


void PompaDroid::menustartCallback(Ref* pSender)
{
	auto scene = Game::create();
	Director::sharedDirector()->replaceScene(scene);
}
