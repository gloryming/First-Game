#pragma once
#include "GameLayer.h"
#include "cocos2d.h"



class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	CREATE_FUNC(GameScene);

	CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);

};
