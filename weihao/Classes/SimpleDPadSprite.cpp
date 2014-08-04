#include "SimpleDPadSprite.h"
#include "LevelLayer.h"

SimpleDPad::SimpleDPad()
{
	WalkToRun = false;
	_isHeld = false;
}

SimpleDPad::~SimpleDPad()
{

}

SimpleDPad* SimpleDPad::dPadWithSpriteFrameName(__String *frameName, float radius)
{
	SimpleDPad *pRet = new SimpleDPad();
	if (pRet && pRet->initWithSpriteFrameName(frameName, radius))
	{
		return pRet;
	}else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SimpleDPad::initWithSpriteFrameName(__String *frameName, float radius)
{
	if (!Sprite::initWithSpriteFrameName(frameName->getCString()))
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

void SimpleDPad::setDPadDirection(DPadDirection dir)
{
	SpriteFrame *frame;
	switch (dir) {
	case NODIR:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_center@2x.png");
		break;
	case RIGHT:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_right@2x.png");
		break;
	case DOWNRIGHT:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downright@2x.png");
		break;
	case DOWN:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_down@2x.png");
		break;
	case DOWNLEFT:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downleft@2x.png");
		break;
	case LEFT:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_left@2x.png");
		break;
	case UPLEFT:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upleft@2x.png");
		break;
	case UP:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_up@2x.png");
		break;
	case UPRIGHT:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upright@2x.png");
		break;
	default:
		return;
	}
	setDisplayFrame(frame);
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
		long _previousTime = _currentTime;
		_currentTime = getCurrentTime();
		if ((_currentTime - _previousTime) < 100 && WalkToRun)
			_delegate->didChangeDirectionToWithRun(this, _direction);
		else
			_delegate->didChangeDirectionTo(this, _direction);
		_isHeld = true;
		return true;
	}
	return false;
}

void SimpleDPad::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	Vec2 location = pTouch->getLocation();
	this->updateDirectionForTouchLocation(location);
	_delegate->didChangeDirectionTo(this, _direction);
}

void SimpleDPad::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	_direction = Vec2::ZERO;
	_isHeld = false;
	setDPadDirection(NODIR);
	//log("%f_%f", _direction.x, _direction.y);
	_delegate->simpleDPadTouchEnded(this);
	long _previousTime = _currentTime;
	_currentTime = getCurrentTime();
	if ((_currentTime - _previousTime) < 100)
		WalkToRun = true;
	else
		WalkToRun = false;
}

void SimpleDPad::updateDirectionForTouchLocation(Vec2 location)
{
	float radians = ccpToAngle(ccpSub(location, this->getPosition()));
	float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

	if (degrees <= 22.5 && degrees >= -22.5)
	{
		//right
		setDPadDirection(RIGHT);
		_direction = ccp(1.0, 0.0);
	}
	else if (degrees > 22.5 && degrees < 67.5)
	{
		//bottomright
		setDPadDirection(DOWNRIGHT);
		_direction = ccp(1.0, -1.0);
	}
	else if (degrees >= 67.5 && degrees <= 112.5)
	{
		//bottom
		setDPadDirection(DOWN);
		_direction = ccp(0.0, -1.0);
	}
	else if (degrees > 112.5 && degrees < 157.5)
	{
		//bottomleft
		setDPadDirection(DOWNLEFT);
		_direction = ccp(-1.0, -1.0);
	}
	else if (degrees >= 157.5 || degrees <= -157.5)
	{
		//left
		setDPadDirection(LEFT);
		_direction = ccp(-1.0, 0.0);
	}
	else if (degrees < -22.5 && degrees > -67.5)
	{
		//topright
		setDPadDirection(UPRIGHT);
		_direction = ccp(1.0, 1.0);
	}
	else if (degrees <= -67.5 && degrees >= -112.5)
	{
		//top
		setDPadDirection(UP);
		_direction = ccp(0.0, 1.0);
	}
	else if (degrees < -112.5 && degrees > -157.5)
	{
		//topleft
		setDPadDirection(UPLEFT);
		_direction = ccp(-1.0, 1.0);
	}
	//log("%f_%f", _direction.x, _direction.y);
}

long SimpleDPad::getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}