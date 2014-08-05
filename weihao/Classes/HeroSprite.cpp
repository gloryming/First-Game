#include"HeroSprite.h"

Hero::Hero()
{
}

Hero::~Hero()
{
}

bool Hero::init()
{
	if (!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"))
	{
		return false;
	}
	this->setCenterToBottom(39.0);
	this->setCenterToSides(29.0);
	this->setHitPoints(100.0);
	this->setDamage(20.0);
	this->setWalkSpeed(80.0);
	this->setRunSpeed(120.0);
	this->setJumpHight(60.0);
	this->setJumpNumLimit(2);

	Animation* idleAnimation = animationWithPrefix("hero_idle", 0, 6, 1.0 / 12.0);
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	Animation* walkAnimation = animationWithPrefix("hero_walk", 0, 8, 1.0 / 12.0);
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	Animation* runAnimation = animationWithPrefix("hero_run", 0, 8, 1.0 / 12.0);
	this->setRunAction(RepeatForever::create(Animate::create(runAnimation)));

	Animation* jumpAnimation = animationWithPrefix("hero_jump", 0, 6, 1.0 / 18.0);
	auto jumpAction = JumpBy::create(1.0/3.0, Vec2::ZERO, getJumpHight(), 1);
	auto action = Spawn::create(jumpAction, Animate::create(jumpAnimation), NULL);
	this->setJumpAction(Sequence::create(action, CallFunc::create(this, callfunc_selector(Hero::idle)), NULL));

	Animation* attackAnimation = animationWithPrefix("hero_attack_00",0,2,1.0 / 24.0);
	//this->setAttackAction(RepeatForever::create(Animate::create(attackAnimation)));
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), CallFunc::create(this, callfunc_selector(Hero::idle)), NULL));

	Animation* jumpAttackAnimation = animationWithPrefix("hero_jumpattack", 0, 5, 1.0 / 24.0);
	this->setJumpAttackAction(Sequence::create(Animate::create(jumpAttackAnimation), CallFunc::create(this, callfunc_selector(Hero::idle)), NULL));

	Animation* runAttackAnimation = animationWithPrefix("hero_runattack", 0, 6, 1.0 / 24.0);
	this->setRunAttackAction(Sequence::create(Animate::create(runAttackAnimation), CallFunc::create(this, callfunc_selector(Hero::idle)), NULL));

	return true;
}