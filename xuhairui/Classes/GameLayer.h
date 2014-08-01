#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Hero.h"
#include "ControlLayer.h"

class GameLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	//	virtual bool onTouchBegan(Touch *touch, Event *event) override;
	void checkstate();
	void moveBackground();
	void update(float dt);
	void Hero_walk(Point, float);
	void Hero_stop();
	CC_SYNTHESIZE(float, actualWidth, ActualWidth);
	CC_SYNTHESIZE(Hero*, _hero, Hero);
private:
	SpriteBatchNode *spriteSheet;
	TMXTiledMap *map;
};

#endif 
