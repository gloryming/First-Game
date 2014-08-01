#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer()
: _map(NULL)
{
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size winSize = Director::getInstance()->getWinSize();

	_map = TMXTiledMap::create("tiled_map.tmx");
	_map->setAnchorPoint(Vec2(0, 0.5));
	_map->setPosition(Vec2(0, winSize.height/2));
	this->addChild(_map);

	return true;
}