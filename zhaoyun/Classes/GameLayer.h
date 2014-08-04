#pragma once
#include "cocos2d.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC(GameLayer);
	bool init();
private:
	cocos2d::CCTMXTiledMap *map;
};

