#include "OperateLayer.h"
#include "Hero.h"

USING_NS_CC;

OperateLayer::OperateLayer()
: _operator(NULL)
, _hero(NULL)
{
}

OperateLayer::~OperateLayer()
{
}

bool OperateLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size winSize = Director::getInstance()->getWinSize();

	_operator = Sprite::create("dpad_center.png");
	_operator->setPosition(Vec2(60, 70));
	_operator->setOpacity(120);
	this->addChild(_operator);

	_buttonA = Sprite::create("button_a_normal.png");
	_buttonA->setPosition(Vec2(winSize.width - 120, 70));
	_buttonA->setOpacity(120);
	this->addChild(_buttonA);

	_buttonB = Sprite::create("button_b_normal.png");
	_buttonB->setPosition(Vec2(winSize.width - 50, 70));
	_buttonB->setOpacity(120);
	this->addChild(_buttonB);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(OperateLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(OperateLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(OperateLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool OperateLayer::onTouchBegan(Touch* touch, Event* unused)
{
	Vec2 touchPoint = touch->getLocation();
	Vec2 dPadPoint = _operator->getPosition();
	Direction dir;

	Rect dPadRect = Rect(_operator->getPositionX() - _operator->getContentSize().width / 2,
		_operator->getPositionX() - _operator->getContentSize().height / 2,
		_operator->getContentSize().width,
		_operator->getContentSize().height);
	Rect buttonARect = Rect(_buttonA->getPositionX() - _buttonA->getContentSize().width / 2,
		_buttonA->getPositionY() - _buttonA->getContentSize().height / 2,
		_buttonA->getContentSize().width,
		_buttonA->getContentSize().height);
	Rect buttonBRect = Rect(_buttonB->getPositionX() - _buttonB->getContentSize().width / 2,
		_buttonB->getPositionY() - _buttonB->getContentSize().height / 2,
		_buttonB->getContentSize().width,
		_buttonB->getContentSize().height);

	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_center.png");;
	
	if (dPadRect.containsPoint(touchPoint))
	{

		log("D Pad");
		float radians = ccpToAngle(dPadPoint - touchPoint);
		float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);
		log("degree: %f", degrees);
		if (degrees >= -22.5 && degrees < 22.5)
			dir = DIR_LEFT;
		else if (degrees >= 22.5 && degrees < 67.5)
			dir = DIR_UPLEFT;
		else if (degrees >= 67.5 && degrees < 112.5)
			dir = DIR_UP;
		else if (degrees >= 112.5 && degrees < 157.5)
			dir = DIR_UPRIGHT;
		else if (degrees >= 157.5 || degrees <= -157.5)
			dir = DIR_RIGHT;
		else if (degrees >= -67.5 && degrees < -22.5)
			dir = DIR_DOWNLEFT;
		else if (degrees >= -112.5 && degrees < -67.5)
			dir = DIR_DOWN;
		else if (degrees >= -157.5 && degrees < -112.5)
			dir = DIR_DOWNRIGHT;

		switch (dir)
		{
		case DIR_LEFT:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_left.png");
			_hero->walk(DIR_LEFT);
			_hero->setRunTimer(20);
			break;
		case DIR_UPLEFT:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upleft.png");
			_hero->walk(DIR_UPLEFT);
			_hero->setRunTimer(20);
			break;
		case DIR_UP:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_up.png");
			_hero->walk(DIR_UP);
			_hero->setRunTimer(20);
			break;
		case DIR_UPRIGHT:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upright.png");
			_hero->walk(DIR_UPRIGHT);
			_hero->setRunTimer(20);
			break;
		case DIR_RIGHT:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_right.png");
			_hero->walk(DIR_RIGHT);
			_hero->setRunTimer(20);
			break;
		case DIR_DOWNLEFT:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downleft.png");
			_hero->walk(DIR_DOWNLEFT);
			_hero->setRunTimer(20);
			break;
		case DIR_DOWN:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_down.png");
			_hero->walk(DIR_DOWN);
			_hero->setRunTimer(20);
			break;
		case DIR_DOWNRIGHT:
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downright.png");
			_hero->walk(DIR_DOWNRIGHT);
			_hero->setRunTimer(20);
			break;
		default:
			break;
		}
	}
	else if (buttonARect.containsPoint(touchPoint))
	{
		log("A");
		if (_hero->getChangable())
		{
			_hero->attack();
			_hero->setAttackTimer(60);
		}
	}
	else if (buttonBRect.containsPoint(touchPoint))
	{
		log("B");
		_hero->jump(_hero->getDir());
	}
	else
	{
		return false;
	}

	_operator->setDisplayFrame(frame);
	return true;
}

void OperateLayer::onTouchMoved(Touch* touch, Event* unused)
{
}

void OperateLayer::onTouchEnded(Touch* touch, Event* unused)
{
	_operator->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_center.png"));
	_hero->stop();
}