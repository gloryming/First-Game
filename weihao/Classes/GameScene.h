#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "HeroSprite.h"
#include "HudLayer.h"
#include "LevelLayer.h"

USING_NS_CC;

class Game : public Scene
{
public:
	Game(void);
	~Game(void);

	CREATE_FUNC(Game);
	bool init();

	CC_SYNTHESIZE(Level*, _level, level);
	CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);
};

#endif