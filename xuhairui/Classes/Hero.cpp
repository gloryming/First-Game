#include "Hero.h"
#include "ActionSprite.h"
USING_NS_CC;

Hero::Hero() :walkSpeed(0)
//, DirectionX(Point(0,0))
, centerToBottom(0.0)
, centerToSides(0)
, attacktimes(0)
, heroState(kActionStateNone)
, jumptimes(1)
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
	Animation* jumpAnimation = ActionSprite::animationWithPrefix("hero_jump", 0, 6, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(jumpAnimation, "hero_jump");
	Animation* jumpattackAnimation = ActionSprite::animationWithPrefix("hero_jumpattack", 0, 5, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(jumpattackAnimation, "hero_jumpattack");
	Animation* runattackAnimation = ActionSprite::animationWithPrefix("hero_runattack", 0, 6, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(runattackAnimation, "hero_runattack");
	Animation* attack_00_Animation = ActionSprite::animationWithPrefix("hero_attack_00", 0, 3, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(attack_00_Animation, "hero_attack_00");
	Animation* attack_01_Animation = ActionSprite::animationWithPrefix("hero_attack_01", 0, 3, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(attack_01_Animation, "hero_attack_01");
	Animation* attack_02_Animation = ActionSprite::animationWithPrefix("hero_attack_02", 0, 5, 1.0 / 12.0);
	AnimationCache::getInstance()->addAnimation(attack_02_Animation, "hero_attack_02");

	this->setWalkSpeed(1);
	this->setRunSpeed(2);
//	this->setDirectionX(Point(0,0));
	this->setcenterToBottom(39.0); 
	this->setcenterToSides(29.0); 
	heroState=kActionStateIdle;
	lastHeroState = kActionStateIdle;
	herodirection = None;
	log("start action ");
	this->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_idle"))));
	log("end");
	return true;
}

void Hero::Runidleaction()
{
		this->stopAllActions();
		this->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_idle"))));
}

void Hero::Runwalkaction()
{
		log("walk");
		this->stopAllActions();
		auto walkaction = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_walk")));
		this->runAction(walkaction);
}

void Hero::Runrunaction()
{
		log("run");
		this->stopAllActions();
		auto runaction = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_run")));
		this->runAction(runaction);
}

void Hero::Runjumpaction(){
		this->stopAllActions();
		auto actionJumpDone = CallFuncN::create([&](Ref* sender){
			log("change");
			this->setPosition(getHeroposition());
			updateHerostate(kActionStateIdle);
			setJumptimes(1);
		});
		auto jumpaction = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("hero_jump")),
			actionJumpDone,
			CallFunc::create(this, callfunc_selector(Hero::Runidleaction)),
			NULL);
		this->runAction(jumpaction);
}

void Hero::Runjumpacctackaction()
{
	this->stopAllActions();
	auto actionJumpDone = CallFuncN::create([&](Ref* sender){
		this->setPosition(getHeroposition());
		setJumptimes(1);
		updateHerostate(kActionStateIdle);
		log("jumpattack");
	});
	auto jumpattack = Animate::create(AnimationCache::getInstance()->getAnimation("hero_jumpattack"));
	this->runAction(Sequence::create(jumpattack, actionJumpDone, CallFunc::create(this, callfunc_selector(Hero::Runidleaction)), NULL));
}

void Hero::Runattack_00_action()
{
	this->stopAllActions();
	auto attack_00 = Animate::create(AnimationCache::getInstance()->getAnimation("hero_attack_00"));
	this->runAction(Sequence::create(attack_00, CallFunc::create(this, callfunc_selector(Hero::Runattack_01_action)), NULL));
}

void Hero:: Runattack_01_action()
{   
	if (this->getAttacktimes()<2)
	{
		setAttacktimes(0);
		this->stopAllActions();
		updateHerostate(kActionStateIdle);
		this->Runidleaction();
		log("attack_error_01");
		return;
	}
	auto attack_01 = Animate::create(AnimationCache::getInstance()->getAnimation("hero_attack_01"));
	this->runAction(Sequence::create(attack_01, CallFunc::create(this, callfunc_selector(Hero::Runattack_02_action)), NULL));
}

void Hero::Runattack_02_action()
{
	if (this->getAttacktimes()<3)
	{
		setAttacktimes(0);
		this->stopAllActions();
		updateHerostate(kActionStateIdle);
		this->Runidleaction();
		log("attack_error_02");
		return;
	}
	auto actionAttackDone = CallFuncN::create([&](Ref* sender){
		updateHerostate(kActionStateIdle);
		setAttacktimes(0);
		this->Runidleaction();
		log("attack_02");
	});
	auto attack_02 = Animate::create(AnimationCache::getInstance()->getAnimation("hero_attack_02"));
	this->runAction(Sequence::create(attack_02, actionAttackDone,NULL));
}

void Hero::Runrunattackaction()
{
	this->stopAllActions();
	auto actionJumpDone = CallFuncN::create([&](Ref* sender){
		this->setPosition(getHeroposition());
		updateHerostate(kActionStateIdle);
		this->Runidleaction();
		log("runattack");
	});
	auto runattack = Animate::create(AnimationCache::getInstance()->getAnimation("hero_runattack"));
	this->runAction(Sequence::create(runattack, actionJumpDone, NULL));
}

void Hero::updateHerostate(ActionState action)
{
	lastHeroState = heroState;
	heroState = action;
}

