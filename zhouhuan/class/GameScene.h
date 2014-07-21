#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "OperateLayer.h"


class GameScene : public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);

	

	virtual bool init();

	CREATE_FUNC(GameScene);
	//static cocos2d::Scene *createScene();

	GameLayer* _gameLayer;
	OperateLayer* _operate;
	//static cocos2d::Scene* createScene();
};
