#include "DPad.h"

USING_NS_CC;

DPad::DPad(){

}

DPad::~DPad(){

}

bool DPad::init(){
	bool ret = false;
	do {
		CC_BREAK_IF(!this->initWithSpriteFrameName("dpad_center@2x.png"));
		m_radius = 64;//
		m_direction = CCPointZero;
		m_isHeld = false;

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(DPad::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(DPad::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(DPad::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		this->scheduleUpdate();
		ret = true;
	} while (0);

	return ret;
}

//void DPad::onEnterTransitionDidFinish(){
//	//
//}

//void DPad::onExit(){
//	//_eventDispatcher->removeEventListener(listener);
//	Director::sharedDirector()->getEventDispatcher()->removeEventListenersForTarget(this);
//}

void DPad::update(float dt){
	if (m_isHeld){
		if (m_direction == Point(1, 0)){
			setSpriteFrame("dpad_right@2x.png");
		}	
		else if (m_direction == Point(0, 1)){
			setSpriteFrame("dpad_up@2x.png");
		}
		else if (m_direction == Point(-1, 0)){
			setSpriteFrame("dpad_left@2x.png");
		}
		else if (m_direction == Point(0, -1)){
			setSpriteFrame("dpad_down@2x.png");
		}
		else if (m_direction == Point(1, 1)){
			setSpriteFrame("dpad_upright@2x.png");
		}
		else if (m_direction == Point(1, -1)){
			setSpriteFrame("dpad_downright@2x.png");
		}
		else if (m_direction == Point(-1, -1)){
			setSpriteFrame("dpad_downleft@2x.png");
		}
		else if (m_direction == Point(-1, 1)){
			setSpriteFrame("dpad_upleft@2x.png");
		}		
	}
	else{
		setSpriteFrame("dpad_center@2x.png");
	}
}

bool DPad::onTouchBegan(Touch* touch,Event *unused_event)
{
	Point location = touch->getLocation();
	//log("%f, %f", touch->getLocation().x, touch->getLocation().y);

	float distanceSQ = ccpDistanceSQ(location, this->getPosition());
	if (distanceSQ <= m_radius *m_radius)
	{
		this->updateDirectionFromTouchLocation(location);
		m_isHeld = true;
		return true;
	}
	return false;
}

void DPad::onTouchMoved(Touch* touches, cocos2d::Event *unused_event)
{
	Point location = touches->getLocation();

	float distanceSQ = ccpDistanceSQ(location, this->getPosition());

	m_hero->walk(m_direction,distanceSQ);

	this->updateDirectionFromTouchLocation(location);
}

void DPad::onTouchEnded(Touch* touches, cocos2d::Event *unused_event)
{
	m_direction = CCPointZero;
	m_isHeld = false;
	m_hero->stop();

}

void DPad::updateDirectionFromTouchLocation(Point loc)
{
	float radians = ccpToAngle(ccpSub(loc, this->getPosition()));
	float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

	if (degrees <= 22.5&&degrees >= -22.5){
		m_direction = ccp(1.0, 0.0);//right
	}
	else if (degrees > 22.5 && degrees < 67.5)
	{
		m_direction = ccp(1.0, -1.0);//bottomright
	}
	else if (degrees >= 67.5 && degrees <= 112.5)
	{
		m_direction = ccp(0.0, -1.0);//bottom
	}
	else if (degrees > 112.5 && degrees < 157.5)
	{
		m_direction = ccp(-1.0, -1.0);//bottomleft
	}
	else if (degrees >= 157.5 || degrees <= -157.5)
	{
		m_direction = ccp(-1.0, 0.0);//left
	}
	else if (degrees < -22.5 && degrees > -67.5)
	{
		m_direction = ccp(1.0, 1.0);//topright
	}
	else if (degrees <= -67.5 && degrees >= -112.5)
	{
		m_direction = ccp(0.0, 1.0);//top
	}
	else if (degrees < -112.5 && degrees > -157.5)
	{
		m_direction = ccp(-1.0, 1.0);//topleft
	}

}