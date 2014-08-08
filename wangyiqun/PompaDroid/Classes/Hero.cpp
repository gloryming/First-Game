#include "Hero.h" 

USING_NS_CC;

Hero::Hero()
{}
Hero::~Hero()
{}
bool Hero::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!this->initWithSpriteFrameName("hero_idle_00.png"));
		Animation *IdleAnim = this->createAnimation("hero_idle_%02d.png", 6, 12);
		this->setIdleAction(RepeatForever::create(Animate::create(IdleAnim)));
		Animation *WalkAnim = this->createAnimation("hero_walk_%02d.png", 7, 14);
		this->setWalkAction(RepeatForever::create(Animate::create(WalkAnim)));

		Animation *AttackAnim = this->createAnimation("hero_attack_00_%02d.png", 3, 20);
		this->setAttackAction(Sequence::create(Animate::create(AttackAnim), Character::createIdleCallbackFunc(), NULL));
		Animation *HurtAnim = this->createAnimation("hero_hurt_%02d.png", 3, 12);
		this->setHurtAction(Sequence::create(Animate::create(HurtAnim), Character::createIdleCallbackFunc(), NULL));
		Animation *DeadAnim = this->createAnimation("hero_knockout_%02d.png", 5, 12);
		this->setDeadAction(Sequence::create(Animate::create(DeadAnim), Blink::create(3, 9), NULL));
		Animation *JumpAnim = this->createAnimation("hero_jump_%02d.png", 6, 12);
		this->setJumpAction(Sequence::create(Animate::create(JumpAnim),Character::createIdleCallbackFunc(),NULL));
		ret = true;
	} while (0);
	return ret;
}