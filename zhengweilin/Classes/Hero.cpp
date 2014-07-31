#include "Hero.h"


Hero::Hero()
{
}


Hero::~Hero()
{
}

bool Hero::init(){
	bool ret = false;

	do{

		CallFunc *callbackIdle = CallFunc::create(std::bind(&Hero::idle, this));
		CC_BREAK_IF(!this->initWithSpriteFrameName("hero_idle_00.png"));
		
		//创建idle（空闲）动画，调用后反复播放
		Animation *idle = createAnimation("hero_idle_%02d.png", 6, 12);
		setIdleAction(RepeatForever::create(Animate::create(idle)));

		// 创建walk（行走）动画，同样调用后反复播放
		Animation *walk = createAnimation("hero_walk_%02d.png", 7, 12);
		setWalkAction(RepeatForever::create(Animate::create(walk)));

		// 创建attact（攻击）动画，播放后回调到idle动画
		Animation *attack = createAnimation("hero_attack_00_%02d.png", 3, 12);
		setAttackAction(Sequence::create(Animate::create(attack), callbackIdle, NULL));

		// 创建hurt（受伤）动画，播放后回调到idle动画
		Animation *hurt = createAnimation("hero_hurt_%02d.png", 3, 12);
		setHurtAction(Sequence::create(Animate::create(hurt), callbackIdle, NULL));

		// 创建knockout（被击倒）动画，播放后不做任何调用
		Animation *knockout = createAnimation("hero_knockout_%02d.png", 5, 12);
		setKnockoutAction(Sequence::create(Animate::create(knockout), NULL));
	
		setATK(20);
		setHP(100);
		setVelocity(1);
		setDirection(Point::ZERO);

		ret = true;
	} while (0);

	return ret;
}




