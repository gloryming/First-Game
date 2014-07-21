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

	GameLayer* _gameLayer;
	OperateLayer* _operate;
	//static cocos2d::Scene* createScene();
};
/*#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include <cocos2d.h>

class GameScene
{
public:

	static cocos2d::Scene* createScene();
};


#endif*/
