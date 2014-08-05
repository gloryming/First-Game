#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameLayer;
class OperateLayer;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	GameLayer* _gameLayer;
	OperateLayer* _operateLayer;
};