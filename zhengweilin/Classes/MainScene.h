#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public cocos2d::Scene
{
public:
	MainScene();
	~MainScene();
	
	virtual bool init();
	Layer* layer;
	CREATE_FUNC(MainScene);
	CC_SYNTHESIZE(Layer*, _mLayer, MLayer);
};

