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

	CC_SAFE_RETAIN(m_idleAction);
	CC_SAFE_RETAIN(m_walkAction);

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
	this->walkAction();
	this->setDir(dir);
}

void Hero::stop()
{
	this->idleAction();
}