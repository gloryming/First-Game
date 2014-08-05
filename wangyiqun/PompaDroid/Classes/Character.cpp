#include "Character.h"

USING_NS_CC;

Character::Character():
m_IdleAction(NULL),
m_WalkAction(NULL),
m_AttackAction(NULL),
m_HurtAction(NULL),
m_DeadAction(NULL),
m_curActionState(ACTION_NONE)
{

}

Character::~Character(){
	CC_SAFE_RELEASE_NULL(m_IdleAction);
	CC_SAFE_RELEASE_NULL(m_WalkAction);
	CC_SAFE_RELEASE_NULL(m_AttackAction);
	CC_SAFE_RELEASE_NULL(m_HurtAction);
	CC_SAFE_RELEASE_NULL(m_DeadAction);
}

bool Character::changeState(ActionState actionState){
	if (m_curActionState == ACTION_DEAD || m_curActionState == actionState){
		return false;
	}
	this->stopAllActions();
	this->m_curActionState = actionState;
	return true;
}
//
void Character::runIdleAction(){
	if (changeState(ACTION_IDLE)){
		this->runAction(m_IdleAction);
	}
}
void Character::runWalkAction(){
	if (changeState(ACTION_WALK)){
		this->runAction(m_WalkAction);
	}
}
void Character::runAttackAction(){
	if (changeState(ACTION_ATTACK)){
		this->runAction(m_AttackAction);
	}
}
void Character::runHurtAction(){
	if (changeState(ACTION_IDLE)){
		this->runAction(m_HurtAction);
	}
}
void Character::runDeadAction(){
	if (changeState(ACTION_DEAD)){
		this->runAction(m_DeadAction);
	}
}
//
Animation* Character::createAnimation(const char* format,int frameCout,int fps ){
	//Array *Frames = Array::createWithCapacity(frameCout);
	Vector<SpriteFrame*> Frames(frameCout);
	for (int i = 0; i < frameCout;++ i){
		const char* imgName = String::createWithFormat(format, i)->getCString();
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		Frames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(Frames, 1.0 / fps);
}

CallFunc* Character::createIdleCallbackFunc()
{
	return CallFunc::create(CC_CALLBACK_0(Character::runIdleAction, this));
}