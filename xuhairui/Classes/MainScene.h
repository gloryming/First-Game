#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "ControlLayer.h"
#include "GameLayer.h"

class MainScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(MainScene);
	GameLayer *gameLayer;
	ControlLayer* controlLayer;
	bool init();
};

#endif 
