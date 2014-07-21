#include"GameScene.h"
//#include"OperateLayer.h"
USING_NS_CC;

GameScene::GameScene(void )
{
	this->_gameLayer = NULL;
	this->_operate = NULL;
}

GameScene::~GameScene(void )
{

}

bool GameScene::init()
{
	if(!Scene::init())
	{
		return false;
	}
	_gameLayer = GameLayer ::create(); 
	this->addChild (_gameLayer,0);

	_operate = OperateLayer::create();
	this->addChild(_operate, 0);
	_operate->setHero(_gameLayer->getHero());
	return true;
}
/*Scene* GameScene::createScene()
{
 auto scene = Scene::create();
 
 auto gameLayer = GameLayer::create();
 scene->addChild(gameLayer, 0);
 return scene;
}*/
/*#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"

using namespace cocos2d;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	
	auto gameLayer = GameLayer::create();
	scene->addChild(gameLayer, 0);

	auto operateLayer = OperateLayer::create();
	scene->addChild(operateLayer, 1);
	operateLayer->setHero(gameLayer->getHero());

	return scene;
}*/
