#include "MainScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add the background
	Sprite* background = Sprite::create("bg_title.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(origin);
	this->addChild(background, -1);

	// add the title on the background
	Sprite* title = Sprite::create("txt_title.png");
	title->setPosition(Vec2(winSize.width / 2, 220));
	this->addChild(title, 0);

	// add the menu
	auto miStart = MenuItemImage::create("txt_touchtostart.png", 
		"txt_touchtostart.png",
		CC_CALLBACK_1(MainScene::menuStartCallback, this));
	miStart->setPosition(Vec2(winSize.width / 2, 130));

	auto menu = Menu::create(miStart, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);
    
    return true;
}


void MainScene::menuStartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::create());
}
