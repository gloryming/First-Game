#include "MainScene.h"
#include "ControlLayer.h"
#include "GameLayer.h"
USING_NS_CC;


bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	gameLayer = GameLayer::create();
	controlLayer = ControlLayer::create();
	this->addChild(gameLayer, 0);
	this->addChild(controlLayer, 1);
	controlLayer->setHero(gameLayer->getHero());
	return true;
}
