#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__

#include "cocos2d.h"
#include "Defines.h"
#include "Hero.h"
USING_NS_CC;
class ControlLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	void judgeDirection(Sprite *,Point touch);
	CREATE_FUNC(ControlLayer);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchMoved(Touch*touch, Event*event);
	CC_SYNTHESIZE(Hero*, _hero, Hero);
	long ControlLayer::getCurrentTime();
private:
	Sprite *dpad_center;
	Sprite *button_a;
	Sprite *button_b;
	long  time;
};

#endif 
