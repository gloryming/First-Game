#include "Robot.h"

USING_NS_CC;

Robot::Robot():m_nextJudgementTime(0){

}

Robot::~Robot(){

}

bool Robot::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF(!this->initWithSpriteFrameName("robot_base_idle_00.png"));

		Animation* IdleAnim = this->createAnimation("robot_base_idle_%02d.png", 5, 12);
		this->setIdleAction(RepeatForever::create(Animate::create(IdleAnim)));
		Animation* WalkAnim = this->createAnimation("robot_base_walk_%02d.png", 6, 12);
		this->setWalkAction(RepeatForever::create(Animate::create(WalkAnim)));
		Animation* AttackAnim = this->createAnimation("robot_base_attack_%02d.png", 5, 20);
		this->setAttackAction(Sequence::create(Animate::create(AttackAnim), Character::createIdleCallbackFunc(), NULL));
		Animation* HurtAnim = this->createAnimation("robot_base_hurt_%02d.png", 3, 20);
		this->setHurtAction(Sequence::create(Animate::create(HurtAnim), Character::createIdleCallbackFunc(), NULL));
		Animation* DeadAnim = this->createAnimation("robot_base_knockout_%02d.png", 5, 12);
		this->setDeadAction(Sequence::create(Animate::create(DeadAnim), Blink::create(3, 9), NULL));

		ret = true;
	} while (0);

	return ret;
}

void Robot::execute(const Point& target, float targetBodyWidth){
	if (m_nextJudgementTime == 0){
		this->judge(target, targetBodyWidth);
	}
	else{
		--m_nextJudgementTime;
	}
}

void Robot::judge(const Point& target, float targetBodyWidth){
	Point loc = this->getPosition();
	float distance = loc.getDistance(target);
	float area = distance - (targetBodyWidth / 2+this->getDisplayFrame()->getRect().size.width/2)+110;
	float m=(targetBodyWidth / 2 + this->getDisplayFrame()->getRect().size.width / 2);
	bool isFlippedX = this->isFlippedX();
	bool isOnTargetLeft(loc.x < target.x ? true : false);
	if ((isFlippedX&&isOnTargetLeft) || (!isFlippedX&&!isOnTargetLeft)){
		this->m_robotState = (CCRANDOM_0_1()>0.5f ? ROBOT_WANDER : ROBOT_IDLE);
	}
	else { if(area < m_catchArea){
		this->m_robotState = (area < m_attackArea ? ROBOT_ATTACK : ROBOT_PURSUE);
	}
	else{
		this->m_robotState = (CCRANDOM_0_1()>0.5f ? ROBOT_WANDER : ROBOT_IDLE);
	}
	}
	switch (m_robotState){
	case ROBOT_ATTACK:{
						  this->runAttackAction();
						  this->attack();
						  this->m_nextJudgementTime = 50;
						  break;
	}
	case ROBOT_IDLE:{
						this->runIdleAction();
						this->m_nextJudgementTime = CCRANDOM_0_1() * 100;
						break;

	}
	case ROBOT_PURSUE:{
						  this->runWalkAction();
						  this->m_moveDirection = (target-loc).getNormalized();
						  this->setFlippedX(m_moveDirection.x<0 ? true : false);
						  m_moveDirection.x = m_moveDirection.x > 0 ? (m_moveDirection.x + m_velocity.x) : (m_moveDirection.x - m_velocity.x);
						  m_moveDirection.y = m_moveDirection.y > 0 ? (m_moveDirection.y + m_velocity.y) : (m_moveDirection.y - m_velocity.y);
						  this->m_nextJudgementTime = 10;
						  break;
	}
	case ROBOT_WANDER:{
						  this->runWalkAction();
						  this->m_moveDirection.x = CCRANDOM_MINUS1_1();
						  this->m_moveDirection.y = CCRANDOM_MINUS1_1();
						  m_moveDirection.x = m_moveDirection.x > 0 ? (m_moveDirection.x + m_velocity.x) : (m_moveDirection.x - m_velocity.x);
						  m_moveDirection.y = m_moveDirection.y > 0 ? (m_moveDirection.y + m_velocity.y) : (m_moveDirection.y - m_velocity.y);
						  this->m_nextJudgementTime = CCRANDOM_0_1() * 100;
						  break;
	}
	}
}