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

	_operator = Sprite::create("dpad_center@2x.png");
	_operator->setPosition(Vec2(50, 80));
	_operator->setScale(0.5);
	_operator->setOpacity(120);
	this->addChild(_operator);

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

	Rect upleftRect = Rect(15, 90, 23, 22);
	Rect upRect = Rect(38, 90, 23, 37);
	Rect uprightRect = Rect(61, 90, 23, 22);
	Rect leftRect = Rect(2, 68, 47, 22);
	Rect rightRect = Rect(49, 68, 47, 22);
	Rect downleftRect = Rect(15, 46, 23, 22);
	Rect downRect = Rect(38, 31, 23, 37);
	Rect downrightRect = Rect(61, 46, 23, 22);

	SpriteFrame* frame;
	if (upleftRect.containsPoint(touchPoint))
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upleft@2x.png");
		_hero->walk(DIR_UPLEFT);
	}
	else if(upRect.containsPoint(touchPoint))
	{
		log("!");
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_up@2x.png");
		_hero->walk(DIR_UP);
	}
	else if (uprightRect.containsPoint(touchPoint))
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upright@2x.png");
		_hero->walk(DIR_UPRIGHT);
	}
	else if (leftRect.containsPoint(touchPoint))
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_left@2x.png");
		_hero->walk(DIR_LEFT);
	}
	else if (rightRect.containsPoint(touchPoint))
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_right@2x.png");
		_hero->walk(DIR_RIGHT);
	}
	else if (downleftRect.containsPoint(touchPoint))
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downleft@2x.png");
		_hero->walk(DIR_DOWNLEFT);
	}
	else if (downRect.containsPoint(touchPoint))
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_down@2x.png");
		_hero->walk(DIR_DOWN);
	}
	else if (downrightRect.containsPoint(touchPoint))
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downright@2x.png");
		_hero->walk(DIR_DOWNRIGHT);
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
	_operator->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_center@2x.png"));
	_hero->stop();
}
