#include "cocos2d.h"
#pragma once
#include "Defines.h"

USING_NS_CC;

class ActionSprite : public cocos2d::Sprite
{
public:
	ActionSprite();
	~ActionSprite();

	//action methods
	void idle();
	void attack();
	void hurtWithDamage(float damage);
	void knockout();
	void walkWithDirection(Vec2 direction);
	void runWithDirection(Vec2 direction);

	//scheduled methods
	void update(float dt);

	//actions
	CC_SYNTHESIZE_RETAIN(Action*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(Action*, _attackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(Action*, _walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(Action*, _hurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(Action*, _knockedOutAction, KnockedOutAction);
	CC_SYNTHESIZE_RETAIN(Action*, _runAction, RunAction);

	//states
	CC_SYNTHESIZE(ActionState, _actionState, ActionState);

	//attributes
	CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
	CC_SYNTHESIZE(float, _runSpeed, RunSpeed);
	CC_SYNTHESIZE(float, _hitPoints, HitPoints);
	CC_SYNTHESIZE(float, _damage, Damage);

	//movement
	CC_SYNTHESIZE(cocos2d::Vec2, _velocity, Velocity);
	CC_SYNTHESIZE(cocos2d::Vec2, _desiredPosition, DesiredPosition);

	//measurements
	CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
	CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);

	Animation* createAnimation(std::string prefix, int startFrameIdx, int frameCount, float delay);
};