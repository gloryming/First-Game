#pragma once

#include "cocos2d.h"
#include "HeroSprite.h"
#include "SimpleDPadSprite.h"
#include "HudLayer.h"

USING_NS_CC;

class Level : public Layer, public SimpleDPadDelegate
{
public:
	Level();
	~Level();
	virtual bool init() override;
	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, Vec2 direction);
	virtual void isHoldingDirection(SimpleDPad *simpleDPad, Vec2 direction);
	virtual void didChangeDirectionToWithRun(SimpleDPad *simpleDPad, Vec2 direction);
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad);
	CREATE_FUNC(Level);

	void initHero();
	void update(float dt);
	void updatePositions();

	//CC_SYNTHESIZE(HudLayer*, _hud, Hud);
	CC_SYNTHESIZE_RETAIN(TMXTiledMap*, _map, map);
	CC_SYNTHESIZE_RETAIN(TMXLayer*, _tiledMap, tiledMap);
	SpriteBatchNode *_actors;
	SpriteBatchNode *_buttons;
	Hero *_hero;

private:

};
