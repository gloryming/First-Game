#pragma once
#include "cocos2d.h"

USING_NS_CC;

typedef enum {
	NODIR = 0,
	RIGHT,
	DOWNRIGHT,
	DOWN,
	DOWNLEFT,
	LEFT,
	UPLEFT,
	UP,
	UPRIGHT
} DPadDirection;

class SimpleDPad;

class SimpleDPadDelegate
{
public:
	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, Vec2 direction) = 0;
	virtual void isHoldingDirection(SimpleDPad *simpleDPad, Vec2 direction) = 0;
	virtual void didChangeDirectionToWithRun(SimpleDPad *simpleDPad, Vec2 direction) = 0;
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad) = 0;
};

class SimpleDPad : public Sprite
{
public:
	SimpleDPad();
	~SimpleDPad();
	void update(float dt);

	static SimpleDPad* dPadWithSpriteFrameName(__String *frameName, float radius);
	bool initWithSpriteFrameName(__String *frameName, float radius);
	void updateDirectionForTouchLocation(Vec2 location);
	void setDPadDirection(DPadDirection dir);
	long getCurrentTime();

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	CC_SYNTHESIZE(SimpleDPadDelegate*, _delegate, Delegate);
	CC_SYNTHESIZE(bool, _isHeld, IsHeld);
	CC_SYNTHESIZE(float, _radius, Radius);
	CC_SYNTHESIZE(Vec2, _direction, Direction);
	long _currentTime;
	bool WalkToRun;

protected:

};
