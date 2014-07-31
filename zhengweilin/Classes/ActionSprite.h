 #pragma once

#include "cocos2d.h"

using namespace cocos2d;

typedef enum{
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_ATTACK,
	ACTION_STATE_HURT,
	ACTION_STATE_KNOCKOUT,
}ActionState;

class ActionSprite : public cocos2d::Sprite
{
public:
	ActionSprite();
	~ActionSprite();

	void idle();
	void walk(cocos2d::Point direction);
	void attack();
	void hurt(int damage);
	void knockout();

	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _hurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _knockoutAction, KnockoutAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);

	//精灵当前状态
	CC_SYNTHESIZE(ActionState, _currentState, ActionState);

	CC_SYNTHESIZE(float, _velocity, Velocity);	//移动速度
	CC_SYNTHESIZE(cocos2d::Point, _direction, Direction);
	CC_SYNTHESIZE(unsigned int, _hp, HP);
	CC_SYNTHESIZE(unsigned int, _atk, ATK);

protected:

	static cocos2d::Animation *createAnimation(const char *fmt, int count, float fps);

private:

	bool _changeState(ActionState state);
};

