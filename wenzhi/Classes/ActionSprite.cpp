#include "ActionSprite.h"

USING_NS_CC;

ActionSprite::ActionSprite()
: m_idleAction(NULL)
, m_walkAction(NULL)
, m_runAction(NULL)
, m_jumpAction(NULL)
, m_attackAction0(NULL)
, m_attackAction1(NULL)
, m_attackAction2(NULL)
, m_currentState(ACTION_STATE_NONE)
, m_speed(0)
, m_dir(DIR_RIGHT)
, m_runTimer(0)
, m_attackTimer(0)
, m_attackIndex(0)
, m_changable(true)
{
}

ActionSprite::~ActionSprite()
{
}

void ActionSprite::toIdleAction()
{
	if (changeState(ACTION_STATE_IDLE))
	{
		this->runAction(m_idleAction);
	}
	else 
		log("idle false");
}

void ActionSprite::toWalkAction()
{
	if (changeState(ACTION_STATE_WALK))
	{
		this->runAction(m_walkAction);
	}
	else
		log("walk false");
}

void ActionSprite::toRunAction()
{
	if (changeState(ACTION_STATE_RUN))
	{
		this->runAction(m_runAction);
	}
	else
		log("run false");
}

void ActionSprite::toJumpAction()
{
	if (changeState(ACTION_STATE_JUMP))
	{
		this->runAction(m_jumpAction);
		this->runAction(JumpBy::create(0.5f, Vec2(0, 0), 70, 1));
	}
	else
		log("jump false");
}

void ActionSprite::toAttackAction(int index)
{
	if (changeState(ACTION_STATE_ATTACK))
	{
		switch (index)
		{
		case 0: this->runAction(m_attackAction0); break;
		case 1: this->runAction(m_attackAction1); break;
		case 2: this->runAction(m_attackAction2); break;
		default: break;
		}
	}
	else
		log("attack false");
}

Animation* ActionSprite::animationWithPrefix(std::string prefix, int startFrameIdx, int frameCount, float delay)
{
	int idxCount = frameCount + startFrameIdx;
	Vector<SpriteFrame*> frames;
	char name[50];
	SpriteFrame* frame;
	for (int i = startFrameIdx; i < idxCount; i++){
		sprintf(name, "%s_%02d.png", prefix.c_str(), i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		frames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(frames, delay);
}

bool ActionSprite::changeState(ActionState actionState)
{
	if (!m_changable)
	{
		return false;
	}
	this->stopAllActions();
	log("stop!");
	this->setCurrentState(actionState);
	return true;
}