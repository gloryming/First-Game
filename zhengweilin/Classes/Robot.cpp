#include "Robot.h"



Robot::Robot()
{
}


Robot::~Robot()
{
}

bool Robot::init(){
	bool ret = false;

	do{
		CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("robot_idle_00.png"));

		CallFunc *callbackIdle = CallFunc::create(std::bind(&Robot::idle, this));

		// 创建idle（空闲）动画，调用后反复播放
		Animation *idle = createAnimation("robot_idle_%02d.png", 5, 12);
		setIdleAction(RepeatForever::create(Animate::create(idle)));

		// 创建walk（行走）动画，同样调用后反复播放
		Animation *walk = createAnimation("robot_walk_%02d.png", 6, 20);
		setWalkAction(RepeatForever::create(Animate::create(walk)));

		// 创建attact（攻击）动画，播放后回调到idle动画
		Animation *attack = createAnimation("robot_attack_%02d.png", 5, 12);
		setAttackAction(Sequence::create(Animate::create(attack), callbackIdle, NULL));

		// 创建hurt（受伤）动画，播放后回调到idle动画
		Animation *hurt = createAnimation("robot_hurt_%02d.png", 3, 12);
		setHurtAction(Sequence::create(Animate::create(hurt), callbackIdle, NULL));

		// 创建knockout（被击倒）动画，播放后不做任何调用
		Animation *knockout = createAnimation("robot_knockout_%02d.png", 5, 12);
		setKnockoutAction(Sequence::create(Animate::create(knockout), NULL));

		setATK(20); // 攻击力
		setHP(100); // 生命值
		setVelocity(1); // 移动速度
		setDirection(Point::ZERO); // 移动方向

		ret = true;
	} while (0);

	return ret;
}