#pragma once

#include "cocos2d.h"

USING_NS_CC;

class OperationDelegate
{
public:
	// 移动，direction为向量，distance是与起点的直线距离
	virtual void onWalk(cocos2d::Point direction, float distance) = 0;
	// 攻击
	virtual void onAttack() = 0;
	// 停止移动
	virtual void onStop() = 0;
};

typedef enum{
	RIGHT = 0,
	DOWNRIGHT,
	DOWN,
	DOWNLEFT,
	LEFT,
	UPLEFT,
	UP,
	UPRIGHT,
	A,
	B
};

class OperationLayer : public cocos2d::Layer
{
public:

	SpriteBatchNode* _pad;
	Sprite* dpad;
	Sprite* buttonA;
	Sprite* buttonB;

	bool KeyPressed[B + 1];

	OperationLayer();
	~OperationLayer();

	bool init();

	void update(float dt);

	void selectDirection(int degrees);

	CREATE_FUNC(OperationLayer);

	CC_SYNTHESIZE(OperationDelegate*, _delegator, Delegator);
};

