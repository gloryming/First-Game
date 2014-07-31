#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SimpleDPad;

class SimpleDPadDelegate
{
public:
	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, Vec2 direction) = 0;
	virtual void isHoldingDirection(SimpleDPad *simpleDPad, Vec2 direction) = 0;
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad) = 0;
};

class SimpleDPad : public Sprite
{
public:
	SimpleDPad();
	~SimpleDPad();
	void update(float dt);

	static SimpleDPad* dPadWithFile(__String *fileName, float radius);
	bool initWithFile(__String *fileName, float radius);
	void updateDirectionForTouchLocation(Vec2 location);

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	CC_SYNTHESIZE(SimpleDPadDelegate*, _delegate, Delegate);
	CC_SYNTHESIZE(bool, _isHeld, IsHeld);
	CC_SYNTHESIZE(float, _radius, Radius);
	CC_SYNTHESIZE(Vec2, _direction, Direction);

protected:

};
