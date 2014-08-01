#include "Hero.h"
#include "ActionSprite.h"
USING_NS_CC;

Hero::Hero() :walkSpeed(0)
, DirectionX(Point(0,0))
, centerToBottom(0.0)
, centerToSides(0)
, heroState(kActionStateNone)
{}

bool Hero::init(){
	if (!Sprite::init())
		return false;
	std::vector<std::string> searchPath;
	searchPath.push_back("Hero");
	CCFileUtils::getInstance()->setSearchPaths(searchPath);
	Animation* idleAnimation = ActionSprite::animationWithPrefix("hero_idle", 0, 6, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(idleAnimation, "hero_idle");
	Animation* walkAnimation = ActionSprite::animationWithPrefix("hero_walk", 0, 8, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(walkAnimation, "hero_walk");
	Animation* runAnimation = ActionSprite::animationWithPrefix("hero_run", 0, 8, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(runAnimation, "hero_run");
	this->setWalkSpeed(1);
	this->setDirectionX(Point(0,0));
	this->setcenterToBottom(39.0); 
	this->setcenterToSides(29.0); 
	heroState=kActionStateIdle;
	herodirection = None;
	log("start action ");
	this->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_idle"))));
	log("end");
	return true;
}

void Hero::Runidleaction()
{
	if (heroState != kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_idle"))));
		heroState = kActionStateIdle;
	}
}

void Hero::Runwalkaction()
{

	if (herodirection != None)
	{
		this->stopAllActions();
		auto walkaction = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_walk")));
		this->runAction(walkaction);
		heroState = kActionStateWalk;
	}
}
