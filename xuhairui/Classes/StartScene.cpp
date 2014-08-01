#include "StartScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size WinSize = Director::getInstance()->getWinSize();

	auto background = Sprite::create("bg_title.png");
	background->setPosition(Vec2(WinSize.width / 2 , WinSize.height / 2 ));
	this->addChild(background, -20);

	auto title = Sprite::create("txt_title.png");
	title->setPosition(Vec2(WinSize.width / 2 , WinSize.height / 2  + title->getContentSize().height));
	this->addChild(title, 10);

	auto startbtn = Sprite::create("txt_touchtostart.png");
	auto menuItem1=MenuItemSprite::create(startbtn, startbtn, CC_CALLBACK_0(StartScene::menuStartbtnCallback, this));
	auto menu = Menu::create(menuItem1, NULL);
	menu->setPosition(Vec2(WinSize.width / 2, WinSize.height / 2  - title->getContentSize().height / 2));
	addChild(menu, 20);
	return true;
}


void StartScene::menuStartbtnCallback()
{
	log("turn to next scene");
	auto MainScene = MainScene::create();
	Director::getInstance()->replaceScene(MainScene);
}