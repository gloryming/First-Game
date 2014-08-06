#pragma once

#include "cocos2d.h"
#include "Hero.h"
#include "OptionLayer.h"
#include "SimpleDPadSprite.h"

class GameLayer : public Layer, public SimpleDPadDelegate
{
public:
    GameLayer();
    ~GameLayer();

	virtual bool init() override;
	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, Vec2 direction);
	virtual void isHoldingDirection(SimpleDPad *simpleDPad, Vec2 direction);
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad);
	CREATE_FUNC(GameLayer);

	void initHero();
	void update(float dt);
	void updatePositions();

	//CC_SYNTHESIZE(HudLayer*, _hud, Hud);
	CC_SYNTHESIZE_RETAIN(TMXTiledMap*, _map, map);
	CC_SYNTHESIZE_RETAIN(TMXLayer*, _tiledMap, tiledMap);
	SpriteBatchNode *_actors;
	Hero *_hero;
};

// End of Philon_cocos2dx_PompaDroid_GAMELAYER_H_

// Philon
// 2013-10-17
