#include "Hero.h"

USING_NS_CC;

Hero::Hero()
{
}

Hero::~Hero()
{
}

bool Hero::init(){
	if (!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"))
	{
		return false;
	}

	Animation* idleAnimation = animationWithPrefix("hero_idle", 0, 6, 1.0 / 12.0);
	m_idleAction = RepeatForever::create(Animate::create(idleAnimation));

	Animation* walkAnimation = animationWithPrefix("hero_walk", 0, 8, 1.0 / 12.0);
	m_walkAction = RepeatForever::create(Animate::create(walkAnimation));

	Animation* runAnimation = animationWithPrefix("hero_run", 0, 8, 1.0 / 12.0);
	m_runAction = RepeatForever::create(Animate::create(runAnimation));

	Animation* jumpAnimation = animationWithPrefix("hero_jump", 0, 6, 1.0 / 12.0);
	m_jumpAction = Repeat::create(Animate::create(jumpAnimation), 1);

	Animation* attackAnimation0 = animationWithPrefix("hero_attack_00", 0, 3, 1.0 / 12.0);
	m_attackAction0 = Repeat::create(Animate::create(attackAnimation0), 1);

	Animation* attackAnimation1 = animationWithPrefix("hero_attack_01", 0, 3, 1.0 / 12.0);
	m_attackAction1 = Repeat::create(Animate::create(attackAnimation1), 1);

	Animation* attackAnimation2 = animationWithPrefix("hero_attack_02", 0, 5, 1.0 / 12.0);
	m_attackAction2 = Repeat::create(Animate::create(attackAnimation2), 1);

	CC_SAFE_RETAIN(m_idleAction);
	CC_SAFE_RETAIN(m_walkAction);
	CC_SAFE_RETAIN(m_runAction);
	CC_SAFE_RETAIN(m_jumpAction);
	CC_SAFE_RETAIN(m_attackAction0);
	CC_SAFE_RETAIN(m_attackAction1);
	CC_SAFE_RETAIN(m_attackAction2);

	this->m_speed = 1.0f;
	
	return true;
}

void Hero::walk(Direction dir)
{
	if (dir == DIR_LEFT || dir == DIR_UPLEFT || dir == DIR_DOWNLEFT)
	{
		this->setSpeed(-abs(this->getSpeed()));
		log("speed: %f", this->getSpeed());
		this->setFlippedX(true);
	}
	else if (dir == DIR_RIGHT || dir == DIR_UPRIGHT || dir == DIR_DOWNRIGHT)
	{
		this->setSpeed(abs(this->getSpeed()));
		this->setFlippedX(false);
	}

	if (this->getRunTimer() && dir == this->getDir())
	{
		this->toRunAction();
	}
	else
	{
		this->toWalkAction();
		this->setDir(dir);
	}
}

void Hero::stop()
{
	this->toIdleAction();
}

void Hero::stop(float dt)
{
	this->setChangable(true);
	this->toIdleAction();
}

void Hero::jump(Direction dir)
{
	this->toJumpAction();
	this->setChangable(false);
	scheduleOnce(schedule_selector(Hero::stop), 0.5f);
	this->setDir(dir);
}

void Hero::attack()
{
	if (this->getAttackTimer())
	{
		this->setAttackIndex(this->getAttackIndex() + 1);
		if (this->getAttackIndex() > 2)
		{
			this->setAttackIndex(0);
		}
	}
	this->toAttackAction(this->getAttackIndex());
	this->setChangable(false);
	if (this->getAttackIndex() == 2)
		scheduleOnce(schedule_selector(Hero::stop), 5.0f / 12.0f);	
	else
		scheduleOnce(schedule_selector(Hero::stop), 3.0f / 12.0f);
}
