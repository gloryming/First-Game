#include "ControlLayer.h"
USING_NS_CC;


bool ControlLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	std::vector<std::string> searchPath;
	searchPath.push_back("joypad.atlas");
	CCFileUtils::getInstance()->setSearchPaths(searchPath);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dPad.plist");
	SpriteBatchNode *btns = SpriteBatchNode::create("dPad.pvr.ccz");
	this->addChild(btns);


	dpad_center = CCSprite::createWithSpriteFrameName("dpad_center@2x.png");
	dpad_center->setPosition(Point(dpad_center->getContentSize().width/2,dpad_center->getContentSize().height/2));
	dpad_center->setOpacity(180);
	this->addChild(dpad_center);
	
	button_a = CCSprite::createWithSpriteFrameName("button_a_normal@2x.png");
	button_a->setPosition(Point(winSize.width-3*button_a->getContentSize().width/2,button_a->getContentSize().height/2));
	button_a->setOpacity(180);
	this->addChild(button_a);
	
	button_b = CCSprite::createWithSpriteFrameName("button_b_normal@2x.png");
	button_b->setPosition(Point(winSize.width-button_b->getContentSize().width/2, button_b->getContentSize().height/2));
	button_b->setOpacity(180);
	this->addChild(button_b);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(ControlLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ControlLayer::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ControlLayer::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, dpad_center);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), button_a);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), button_b);

	//getHero()->setHeroDirection ( None);
	return true;
}

void ControlLayer::judgeDirection(Sprite *target,Point touch)
{
	Node  *circle_dot = Node::create();
	circle_dot->setPosition(Vec2(target->getContentSize().width / 2, target->getContentSize().height / 2));
	Point locationInNode = circle_dot->convertToNodeSpace(touch);
	auto Angle = locationInNode.getAngle();
	auto AngleNumber = CC_RADIANS_TO_DEGREES(Angle);
	SpriteFrame *temp;
	if (AngleNumber <= 22.5&&AngleNumber >= -22.5)
	{
		getHero()->setHeroDirection(Right);
		temp=SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_right@2x.png");
	}
	else if (AngleNumber > 22.5&&AngleNumber <= 67.5)
	{
		getHero()->setHeroDirection(UpRight);
		temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upright@2x.png");
	}
	else if (AngleNumber > 67.5&&AngleNumber < 112.5)
	{
		getHero()->setHeroDirection(Up);
		temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_up@2x.png");
	}
	else if (AngleNumber>112.5&&AngleNumber < 157.5)
	{
		getHero()->setHeroDirection(UpLeft);
		temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_upleft@2x.png");
	}
	else if (AngleNumber>157.5 || AngleNumber < -157.5)
	{
		getHero()->setHeroDirection(Left);
		temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_left@2x.png");
	}
	else if (AngleNumber<-22.5&&AngleNumber >= -67.5)
	{
		getHero()->setHeroDirection(DownRight);
		temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downright@2x.png");
	}
	else if (AngleNumber < -67.5&&AngleNumber >= -112.5)
	{
		getHero()->setHeroDirection(Down);
		temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_down@2x.png");
	}
	else if (AngleNumber < -112.5&&AngleNumber >= -157.5)
	{
		getHero()->setHeroDirection(DownLeft);
		temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_downleft@2x.png");
	}
	dpad_center->setDisplayFrame(temp);
}

bool ControlLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);
	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);

	if (rect.containsPoint(locationInNode))
	{
		if (target == dpad_center)
		{
			long temp = time;
			time=getCurrentTime();
			judgeDirection(target, touch->getLocation());
			if (time - temp > 500)
			{
				getHero()->updateHerostate(kActionStateWalk);
				getHero()->Runwalkaction();
			}
			else
			{
				getHero()->updateHerostate(kActionStateRun);
				getHero()->Runrunaction();
			}
		}
		else if (target == button_a)
		{
			log("target_a");
			SpriteFrame *temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_a_selected@2x.png");
			button_a->setSpriteFrame(temp);
			if (getHero()->getHeroState() == kActionStateJump)
			{
				getHero()->updateHerostate(kActionStateJumpattack);
				getHero()->Runjumpacctackaction();
			}
			else if (getHero()->getHeroState() == kActionStateRun)
			{
				getHero()->updateHerostate(kActionStateRunattack);
				getHero()->Runrunattackaction();
			}
			else if (getHero()->getHeroState() == kActionStateIdle || getHero()->getHeroState() == kActionStateAttack)
			{				
				
				getHero()->updateHerostate(kActionStateAttack);
				if (getHero()->getAttacktimes()==0)
				   getHero()->Runattack_00_action();
				int tmp = getHero()->getAttacktimes();
				getHero()->setAttacktimes(++tmp);

			}
		}
		else if (target == button_b)
		{
			SpriteFrame *temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_b_selected@2x.png");
			button_b->setSpriteFrame(temp);
			if (getHero()->getHeroState()==kActionStateIdle)
			{
			   getHero()->updateHerostate(kActionStateJump);
			   getHero()->Runjumpaction();
			}
		}
		else{
			//chooseTowerType = ANOTHER;
			log("error");
		}
		return true;
	}
	return false;
}

void ControlLayer::onTouchMoved(Touch*touch, Event*event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);
	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);

	if (rect.containsPoint(locationInNode))
	{
		if (target == dpad_center)
		{
			judgeDirection(target,touch->getLocation());
		}
		else if (target == button_a)
		{
			log("target_a");

		}
		else if (target == button_b)
		{
			log("target_b");
		}
		else{
			//chooseTowerType = ANOTHER;
			log("error");
		}
		
	}
}

void ControlLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	if (target == dpad_center)
	{
		getHero()->setHeroDirection ( None);
		getHero()->setHeroState(kActionStateIdle);
		getHero()->Runidleaction();
		SpriteFrame *temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("dpad_center@2x.png");
		dpad_center->setSpriteFrame(temp);

	}
	else if (target == button_a)
	{
		log("target_a");
		SpriteFrame *temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_a_normal@2x.png");
		button_a->setSpriteFrame(temp);

	}
	else if (target == button_b)
	{
		SpriteFrame *temp = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_b_normal@2x.png");
		button_b->setSpriteFrame(temp);
	}
	else{
		//chooseTowerType = ANOTHER;
		log("error");
	}
	
}

long ControlLayer::getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}