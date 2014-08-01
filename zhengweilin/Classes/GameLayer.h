#pragma once
#include "cocos2d.h"
#include "ActionSprite.h"
#include "Hero.h"
#include "Robot.h"


using namespace cocos2d;

class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual bool init();
	CREATE_FUNC(GameLayer);

private:
	cocos2d::TMXTiledMap* _map;

	ActionSprite *_hero;
	cocos2d::Array *_robots;
	cocos2d::SpriteBatchNode *_actors;
};

