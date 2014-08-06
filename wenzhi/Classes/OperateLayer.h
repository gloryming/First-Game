#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Hero;

class OperateLayer : public Layer
{
public:
	OperateLayer();
	~OperateLayer();

	virtual bool init();
	CREATE_FUNC(OperateLayer);

	virtual bool onTouchBegan(Touch* touch, Event* unused) override;
	virtual void onTouchMoved(Touch* touch, Event* unused) override;
	virtual void onTouchEnded(Touch* touch, Event* unused) override;

	CC_SYNTHESIZE(Hero*, _hero, Hero);
	Sprite* _operator;
	Sprite* _buttonA;
	Sprite* _buttonB;
};