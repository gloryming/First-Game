#include "GameScene.h"
#include "GameLayer.h"

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

	return true;
}