#pragma once

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_RUN,
	ACTION_STATE_JUMP,
	ACTION_STATE_ATTACK,
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

	void toIdleAction();
	void toWalkAction();
	void toRunAction();
	void toJumpAction();
	void toAttackAction(int index);

	CC_SYNTHESIZE(Action*, m_idleAction, IdeleAction);
	CC_SYNTHESIZE(Action*, m_walkAction, WalkAction);
	CC_SYNTHESIZE(Action*, m_runAction, RunAction);
	CC_SYNTHESIZE(Action*, m_jumpAction, JumpAction);
	CC_SYNTHESIZE(Action*, m_attackAction0, AttackAction0);
	CC_SYNTHESIZE(Action*, m_attackAction1, AttackAction1);
	CC_SYNTHESIZE(Action*, m_attackAction2, AttackAction2);

	CC_SYNTHESIZE(ActionState, m_currentState, CurrentState);

	CC_SYNTHESIZE(float, m_speed, Speed);
	CC_SYNTHESIZE(Direction, m_dir, Dir);
	CC_SYNTHESIZE(int, m_runTimer, RunTimer);
	CC_SYNTHESIZE(int, m_attackTimer, AttackTimer);
	CC_SYNTHESIZE(int, m_attackIndex, AttackIndex);

	CC_SYNTHESIZE(bool, m_changable, Changable);

	Animation* animationWithPrefix(std::string prefix, int startFrameIdx, int frameCount, float delay);

private:
	bool changeState(ActionState actionState);
};