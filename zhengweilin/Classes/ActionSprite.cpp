#include "ActionSprite.h"
#include "GameScene.h"

ActionSprite::ActionSprite()
{
	_idleAction = NULL;
	_walkAction = NULL;
	_attackAction = NULL;
	_hurtAction = NULL;
	_knockoutAction = NULL;
}


ActionSprite::~ActionSprite()
{
}


void ActionSprite::idle(){
	if (_changeState(ACTION_STATE_IDLE)){
		runAction(_idleAction);
//原文是Point(0, 0)
		_velocity =	0;
	}
}

void ActionSprite::attack(){
	if (_changeState(ACTION_STATE_ATTACK)){
		runAction(_attackAction);
	}
}

void ActionSprite::walk(Point direction){
	if (_changeState(ACTION_STATE_WALK)){
		runAction(_walkAction);
		_direction = direction;
		//根据精灵的x向量，来判断精灵的正面“朝向”
		_direction.x > 0 ? setFlipX(false) : setFlipX(true);
	}
}


void ActionSprite::hurt(int damage){
	if (_changeState(ACTION_STATE_HURT)){
		runAction(_hurtAction);
		_hp -= damage;
		if (_hp <= 0){
			knockout();
		}
	}
}

void ActionSprite::knockout(){
	if (_changeState(ACTION_STATE_KNOCKOUT)){
		runAction(_knockoutAction);
	}
}

bool ActionSprite::_changeState(ActionState state){
	bool ret = false;

	//精灵被击倒,gg
	if (_currentState == ACTION_STATE_KNOCKOUT){
		goto change_state_failed;
	}

	if (_currentState == state){
		goto change_state_failed;
	}

	this->stopAllActions();

	_currentState = state;

	ret = true;

change_state_failed:
	return ret;
}


Animation* ActionSprite::createAnimation(const char*fmt, int count, float fps){

	Vector<SpriteFrame*> frames(count);

	for (int i = 0; i < count; i++){
		const char *png = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		frames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(frames, 1.0f / fps);
}












