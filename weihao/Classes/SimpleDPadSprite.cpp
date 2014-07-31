#include "SimpleDPadSprite.h"
#include "LevelLayer.h"

SimpleDPad::SimpleDPad()
{
	
}

SimpleDPad::~SimpleDPad()
{

}

SimpleDPad* SimpleDPad::dPadWithFile(__String *fileName, float radius)
{
	SimpleDPad *pRet = new SimpleDPad();
	if (pRet && pRet->initWithFile(fileName, radius))
	{
		return pRet;
	}else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SimpleDPad::initWithFile(__String *fileName, float radius)
{
	if (!Sprite::initWithFile(fileName->getCString()))
		return false;
	_radius = radius;
	_direction = Vec2::ZERO;
	_isHeld = false;
	this->scheduleUpdate();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SimpleDPad::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SimpleDPad::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SimpleDPad::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void SimpleDPad::update(float dt)
{
	if (_isHeld)
	{
		//log("%f_%f",_direction.x,_direction.y);
		_delegate->isHoldingDirection(this, _direction);
	}
}

bool SimpleDPad::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	CCPoint location = pTouch->getLocation();

	float distanceSQ = ccpDistanceSQ(location, this->getPosition());
	if (distanceSQ <= _radius * _radius)
	{
		this->updateDirectionForTouchLocation(location);
		_isHeld = true;
		return true;
	}
	return false;
}

void SimpleDPad::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	CCPoint location = pTouch->getLocation();
	this->updateDirectionForTouchLocation(location);
}

void SimpleDPad::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	_direction = Vec2::ZERO;
	_isHeld = false;
	//log("%f_%f", _direction.x, _direction.y);
	_delegate->simpleDPadTouchEnded(this);
}

void SimpleDPad::updateDirectionForTouchLocation(Vec2 location)
{
	float radians = ccpToAngle(ccpSub(location, this->getPosition()));
	float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

	if (degrees <= 22.5 && degrees >= -22.5)
	{
		//right
		_direction = ccp(1.0, 0.0);
	}
	else if (degrees > 22.5 && degrees < 67.5)
	{
		//bottomright
		_direction = ccp(1.0, -1.0);
	}
	else if (degrees >= 67.5 && degrees <= 112.5)
	{
		//bottom
		_direction = ccp(0.0, -1.0);
	}
	else if (degrees > 112.5 && degrees < 157.5)
	{
		//bottomleft
		_direction = ccp(-1.0, -1.0);
	}
	else if (degrees >= 157.5 || degrees <= -157.5)
	{
		//left
		_direction = ccp(-1.0, 0.0);
	}
	else if (degrees < -22.5 && degrees > -67.5)
	{
		//topright
		_direction = ccp(1.0, 1.0);
	}
	else if (degrees <= -67.5 && degrees >= -112.5)
	{
		//top
		_direction = ccp(0.0, 1.0);
	}
	else if (degrees < -112.5 && degrees > -157.5)
	{
		//topleft
		_direction = ccp(-1.0, 1.0);
	}
	//log("%f_%f", _direction.x, _direction.y);
	_delegate->didChangeDirectionTo(this, _direction);
}