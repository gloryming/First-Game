#pragma once

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
} ActionState;

typedef enum{
	DIR_LEFT = 1,
	DIR_RIGHT, 
	DIR_UP,
	DIR_DOWN,
	DIR_UPLEFT,
	DIR_UPRIGHT,
	DIR_DOWNLEFT,
	DIR_DOWNRIGHT,
} Direction;

class ActionSprite : public Sprite
{
public:
	ActionSprite();
	~ActionSprite();

	void idleAction();
	void walkAction();

	CC_SYNTHESIZE(Action*, m_idleAction, IdeleAction);
	CC_SYNTHESIZE(Action*, m_walkAction, WalkAction);

	CC_SYNTHESIZE(ActionState, m_currentState, CurrentState);

	CC_SYNTHESIZE(float, m_speed, Speed);
	CC_SYNTHESIZE(Direction, m_dir, Dir);

	Animation* animationWithPrefix(std::string prefix, int startFrameIdx, int frameCount, float delay);

private:
	bool changeState(ActionState actionState);
};