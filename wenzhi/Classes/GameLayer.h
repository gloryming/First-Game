#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Hero;

class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual bool init();
	CREATE_FUNC(GameLayer);

	TMXTiledMap* _map;
	CC_SYNTHESIZE(Hero*, _hero, Hero);
	void update(float dt);
	void updateHero(float dt);

private:
	float m_tileWidth;
	float m_tileHeight;
};