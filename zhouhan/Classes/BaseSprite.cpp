/*#include "BaseSprite.h"
//#include "cocos2d.h"

BaseSprite::BaseSprite():
 m_pIdleAction(NULL),
 m_pWalkAction(NULL),
 m_pAttackAction(NULL),
 m_pHurtAction(NULL),
 m_pDeadAction(NULL),
 m_currActionState(ACTION_STATE_NONE)
{
}
BaseSprite::~BaseSprite()
{
 CC_SAFE_RELEASE_NULL(m_pIdleAction);
 CC_SAFE_RELEASE_NULL(m_pWalkAction);
 CC_SAFE_RELEASE_NULL(m_pAttackAction);
 CC_SAFE_RELEASE_NULL(m_pHurtAction);
 CC_SAFE_RELEASE_NULL(m_pDeadAction);
}
void BaseSprite::runIdleAction()
{
 if(changeState(ACTION_STATE_IDLE))
 {
  this->runAction(m_pIdleAction);
 }
}
 
void BaseSprite::runWalkAction()
{
 if(changeState(ACTION_STATE_WALK))
 {
  this->runAction(m_pWalkAction);
 }
}
void BaseSprite::runAttackAction()
{
 if(changeState(ACTION_STATE_ATTACK))
 {
  this->runAction(m_pAttackAction);
 }
}
void BaseSprite::runHurtAction()
{
 if(changeState(ACTION_STATE_HURT))
 {
  this->runAction(m_pHurtAction);
 }
}
void BaseSprite::runDeadAction()
{
 if(changeState(ACTION_STATE_DEAD))
 {
  this->runAction(m_pDeadAction);
 }
}*/

/*  
Animation* BaseSprite::createAnimation(const char* formatStr, int frameCount, int fps)
{
 Array *pFrames = Array::createWithCapacity(frameCount);
 for(int i = 0; i < frameCount; ++ i)
 {
  const char* imgName = String::createWithFormat(formatStr, i)->getCString();
  SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
  pFrames->addObject(pFrame);
 }
 return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}
bool BaseSprite::changeState(ActionState actionState)
{
 if(m_currActionState == ACTION_STATE_DEAD || m_currActionState == actionState)
 {
  return false;
 }
 this->stopAllActions();
 this->m_currActionState = actionState;
 return true;
}
CallFunc* BaseSprite::createIdleCallbackFunc()
{
 return CallFunc::create(CC_CALLBACK_0(BaseSprite::runIdleAction, this));
}*/
/*#include "ActionSprite.h"


USING_NS_CC;
 ActionSprite::ActionSprite() { 
	 _idleAction = NULL; 
	 _walkAction = NULL; 
	 _attackAction = NULL;
	 _hurtAction = NULL; 
	 _knockoutAction = NULL; 
 }

ActionSprite::~ActionSprite()
{}

void ActionSprite::idle()
{
if (_changeState(ACTION_STATE_IDLE)) {
runAction(_idleAction);
_velocity = Point(0, 0);
}
}

void ActionSprite::attack()
{
if (_changeState(ACTION_STATE_ATTACK)) {
runAction(_attackAction);
}

}

void ActionSprite::walk(Point direction)
{
if (_changeState(ACTION_STATE_WALK)) {
runAction(_walkAction);
_direction = direction;
// 根据精灵的x向量，来判断精灵的正面“朝向”
_direction.x > 0 ? setFlipX(true) : setFlipX(false);
}
}

void ActionSprite::hurt(int damage)
{
if (_changeState(ACTION_STATE_HURT)) {
runAction(_hurtAction);
_hp -= damage;
if (_hp <= 0) {
knockout();
}
}
}

void ActionSprite::knockout()
{
if (_changeState(ACTION_STATE_KNOCKOUT)) {
runAction(_knockoutAction);
}
}

bool ActionSprite::_changeState(ActionState state)
{
bool ret = false;

// 精灵已经被击倒（Game Over），就不能再出发其他动作了！
if (_currentState == ACTION_STATE_KNOCKOUT) {
    goto change_state_failed;
}

// 精灵已经处于要改变的状态，就没必要在改变了！
if (_currentState == state) {
    goto change_state_failed;
}

// 改变动作之前，先停止所有动作
this->stopAllActions();

_currentState = state;
ret = true;
change_state_failed:
return ret;
}

Animation *ActionSprite::createAnimation(const char *fmt, int count, float fps)
{
Array *frames = Array::createWithCapacity(count);
int i = 0;

for (i = 0; i < count; i++) {
    const char *png = String::createWithFormat(fmt, i)->getCString();
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
    frames->addObject(frame);
}

return Animation::createWithSpriteFrames(frames, 1.0 / fps);
}*/
#include "BaseSprite.h"

using namespace cocos2d;

BaseSprite::BaseSprite():
	m_pIdleAction(NULL),
	m_pWalkAction(NULL),
	m_currActionState(ACTION_STATE_NONE)
{

}
BaseSprite::~BaseSprite()
{
	CC_SAFE_RELEASE_NULL(m_pIdleAction);
	CC_SAFE_RELEASE_NULL(m_pWalkAction);
	
}

void BaseSprite::runIdleAction()
{
	if(changeState(ACTION_STATE_IDLE))
	{
		this->runAction(m_pIdleAction);
	}
}
	
void BaseSprite::runWalkAction()
{
	if(changeState(ACTION_STATE_WALK))
	{
		this->runAction(m_pWalkAction);
	}
}

bool BaseSprite::isLive()
{
	
		return true;
}
Animation* BaseSprite::createAnimation(const char* formatStr, int frameCount, int fps)
{
	Vector<SpriteFrame *> pFrames ;//= __Array::createWithCapacity(frameCount);
	for(int i = 0; i < frameCount; ++ i)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		if (pFrame)
		{
//			pFrames->addObject(pFrame);
			pFrames.pushBack(pFrame);
		}
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}


CallFunc* BaseSprite::createIdleCallbackFunc()
{
	return  CallFunc::create(CC_CALLBACK_0(BaseSprite::runIdleAction, this));
}

bool BaseSprite::changeState(ActionState actionState)
{
	if((m_currActionState == actionState ) || m_currActionState == actionState)
	{
		return false;
	}

	this->stopAllActions();
	this->m_currActionState = actionState;
}

BoundingBox BaseSprite::createBoundingBox(cocos2d::Point origin, cocos2d::Size size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin= origin;
	boundingBox.original.size= size;
	boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
	boundingBox.actual.size= size;
	return boundingBox;
}



void BaseSprite::updateBoxes() {
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
	if(isFlippedX) {
		x = this->getPosition().x - m_hitBox.original.origin.x;
	}else {
		x = this->getPosition().x + m_hitBox.original.origin.x;
	}
	m_hitBox.actual.origin = Point(x, this->getPosition().y + m_hitBox.original.origin.y);
    m_bodyBox.actual.origin = this->getPosition() + m_bodyBox.original.origin;
}

void BaseSprite::setPosition(const Point &position)
{
	Sprite::setPosition(position);
	this->updateBoxes();
}
