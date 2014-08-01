#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"

USING_NS_CC;

GameScene::GameScene()
: _gameLayer(NULL)
{
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_gameLayer = GameLayer::create();
	this->addChild(_gameLayer, 0);

	_operateLayer = OperateLayer::create();
	_operateLayer->setHero(_gameLayer->getHero());
	this->addChild(_operateLayer, 10);

	scheduleUpdate();

	return true;
}
