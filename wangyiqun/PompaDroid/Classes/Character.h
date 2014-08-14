#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"

typedef enum {
	ACTION_NONE = 0,
	ACTION_IDLE,
	ACTION_WALK,
	ACTION_ATTACK,
	ACTION_HURT,
	ACTION_DEAD,
	ACTION_JUMP
}ActionState;

class Character :public cocos2d::Sprite
{
public:
	Character();
	~Character();
	void runIdleAction();
	void runWalkAction();
	void runAttackAction();
	void runHurtAction();
	void runDeadAction();
	void runJumpAction();

	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_IdleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_WalkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_AttackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_HurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_DeadAction, DeadAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_JumpAction, JumpAction);

	CC_SYNTHESIZE(ActionState, m_curActionState, CurActionStatus);
	CC_SYNTHESIZE(cocos2d::Point, m_velocity, Velocity);
	CC_SYNTHESIZE(unsigned int, m_hp, Hp);
	CC_SYNTHESIZE(unsigned int, m_atk, Atk);

	std::function<void(void)> attack;
	
	cocos2d::CallFunc* createIdleCallbackFunc();
protected:
	static cocos2d::Animation* createAnimation(const char* format, int frameCout, int fps);
private:
	bool changeState(ActionState actionState);
};

#endif//_CHARACTER_H_