#include "OperateLayer.h"

OperateLayer::OperateLayer()
{

}

OperateLayer::~OperateLayer()
{
}
bool OperateLayer::init()
{
	pressdown=false;
	

	bool ret = false;
	do {
		CC_BREAK_IF( !Layer::init() );
		std::vector<std::string> searchbutto;
		searchbutto.push_back("joypad.atlas");
		CCFileUtils::getInstance()->setSearchPaths(searchbutto);
		auto sprite=Sprite::create("dpad_center@2x.png");
		sprite->setAnchorPoint(Point(0,0));
		setPosition(Vec2(0,0));
		this->addChild(sprite);
		o.x=sprite->getPositionX()+sprite->getContentSize().width/2;
		o.y=sprite->getPositionX()+sprite->getContentSize().height/2;


		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(OperateLayer::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(OperateLayer::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(OperateLayer::onTouchesEnded, this); 
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		ret = true;

	} while(false);

	return ret;



	return true;
}

void OperateLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event)

{         
	//Point locInView =touches->getLocationInView();//得到UI坐标
	//Point loc=Director::sharedDirector()->convertToGL(locInView);//把
	Size winSize = Director::getInstance()->getWinSize();
	//vector<Touch*>::const_iterator touchIter = touches.begin();
	Vector<cocos2d::Touch*>::const_iterator touchIter=touches.begin();
	while(touchIter != touches.end())
	{
		Touch *pTouch = (Touch*)(*touchIter);
		Point p = pTouch->getLocation();//OpenGL坐标
		float radians = ccpToAngle(ccpSub(o, p));
		float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);
		if (degrees <= 22.5 && degrees >= -22.5) 
	
		{
			pressdown=true;
			button=Sprite::create("dpad_left@2x.png");
			button->setAnchorPoint(Point(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
             m_pHero->hero_run(); 
		}
		 else if (degrees > 22.5 && degrees < 67.5) 

		{
			pressdown=true;
			button=Sprite::create("dpad_upleft@2x.png");
			button->setAnchorPoint(Point(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
		}
		 else if (degrees >= 67.5 && degrees <= 112.5) 

		{
			pressdown=true;
			button=Sprite::create("dpad_up@2x.png");
			button->setAnchorPoint(Vec2(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
		}
		 else if (degrees > 112.5 && degrees < 157.5) 

		{
			pressdown=true;
			button=Sprite::create("dpad_upright@2x.png");
			button->setAnchorPoint(Point(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
		}
		 else if (degrees >= 157.5 || degrees <= -157.5) 

		{
			pressdown=true;
			button=Sprite::create("dpad_right@2x.png");
			button->setAnchorPoint(Point(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
		}
		 else if (degrees < -22.5 && degrees > -67.5) 

		{
			pressdown=true;
			button=Sprite::create("dpad_downleft@2x.png");
		button->setAnchorPoint(Point(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
		}
		 else if (degrees <= -67.5 && degrees >= -112.5) 

		{
			pressdown=true;
			button=Sprite::create("dpad_down@2x.png");
			button->setAnchorPoint(Point(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
		}
		 else if (degrees < -112.5 && degrees > -157.5) 

		{
			pressdown=true;
			button=Sprite::create("dpad_downright@2x.png");
			button->setAnchorPoint(Point(0,0));
			setPosition(Vec2(0,0));
			this->addChild(button);
		}

		++ touchIter;
	
	}


	return;
}
void OperateLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event)
{
	
	return;
}



void  OperateLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event)

{
	if (pressdown)
	{
		button->removeFromParentAndCleanup(true);
		pressdown=false;
	}

	return;
}