#include "GameLayer.h"

GameLayer::GameLayer()
{
}


GameLayer::~GameLayer()
{
}


bool GameLayer::init(){

	bool ret = false;
	
	do{
		CC_BREAK_IF(!Layer::init());

		_map = TMXTiledMap::create("map.tmx");
		this->addChild(_map);
	
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
		_actors = SpriteBatchNode::create("pd_sprites.pvr.ccz");
		this->addChild(_actors);

		//_hero = Hero::create();
		//_hero->setPosition(80, 80);
		//_hero->idle();

		//_actors->addChild(_hero);

		ret = true;
	} while (0);

	return ret;
}