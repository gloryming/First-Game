#include "LevelLayer.h"

Level::Level()
{
	_map = NULL;
	_tiledMap = NULL;
}

Level::~Level()
{
}

Scene* Level::createScene()
{
	auto scene = Scene::create();
	auto layer = Level::create();
	scene->addChild(layer);

	return scene;
}

bool Level::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		this->setmap(TMXTiledMap::create("map.tmx"));
		this->settiledMap(_map->layerNamed("tiledMap"));
		_tiledMap->setAnchorPoint(Vec2(0, 1));
		_tiledMap->setPosition(Vec2(0,winSize.height));
		this->addChild(_map, 1);
		bRet = true;
	} while (0);

	return bRet;
}