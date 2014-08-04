#include "ActionSprite.h"

USING_NS_CC;

ActionSprite::ActionSprite()
: m_idleAction(NULL)
, m_walkAction(NULL)
, m_currentState(ACTION_STATE_NONE)
, m_speed(0)
, m_dir(DIR_RIGHT)
{
}

ActionSprite::~ActionSprite()
{
}

void ActionSprite::idleAction()
{
	if (changeState(ACTION_STATE_IDLE))
	{
		this->runAction(m_idleAction);
	}
}

void ActionSprite::walkAction()
{
	if (changeState(ACTION_STATE_WALK))
	{
		this->runAction(m_walkAction);
	}
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
	this->stopAllActions();
	this->setCurrentState(actionState);
	return true;
}