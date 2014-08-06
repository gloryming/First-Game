#include "Hero.h"

#include "cocos2d.h"
#include "ActionSprite.h"

using namespace cocos2d;

Hero::Hero()
{}

Hero::~Hero()
{}

bool Hero::init()
{
	if (!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"))
	{
		return false;
	}
	Animation* idleAnimation = createAnimation("hero_idle", 0, 6, 1.0 / 12.0);
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	Animation* walkAnimation = createAnimation("hero_walk", 0, 8, 1.0 / 12.0);
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	Animation* runAnimation = createAnimation("hero_run", 0, 8, 1.0 / 12.0);
	this->setRunAction(RepeatForever::create(Animate::create(runAnimation)));

	//Animation* attackAnimation = createAnimation("hero_attack_00",0,2,1.0 / 24.0);
	//this->setAttackAction(RepeatForever::create(Animate::create(attackAnimation)));

	this->setCenterToBottom(39.0);
	this->setCenterToSides(29.0);
	this->setHitPoints(100.0);
	this->setDamage(20.0);
	this->setWalkSpeed(80.0);
	this->setRunSpeed(120.0);

	return true;
}
