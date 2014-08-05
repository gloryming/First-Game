#include "OperationLayer.h"

#define KEY(W) EventKeyboard::KeyCode::KEY_##W

OperationLayer::OperationLayer()
{
}


OperationLayer::~OperationLayer()
{
}

bool OperationLayer::init(){

	for (int i = 0; i < 9; i++){
		KeyPressed[i] = false;
	}

	bool ret = false;

	do{
		CC_BREAK_IF(!Sprite::create("Hero/hero_idle_00.png"));

		auto listenerKey = EventListenerKeyboard::create();

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pad.plist");
		_pad = SpriteBatchNode::create("pad.png");
		this->addChild(_pad);

		dpad = Sprite::createWithSpriteFrameName("dpad_center@2x.png");
		dpad->setPosition(80, 80);
		dpad->setScale(0.66f);
		dpad->setOpacity(180);
		_pad->addChild(dpad);

		int width = Director::getInstance()->getWinSize().width;

		buttonA = Sprite::createWithSpriteFrameName("button_a_normal@2x.png");
		buttonA->setPosition(width - 50, 80);
		buttonA->setScale(0.5f);
		buttonA->setOpacity(180);
		_pad->addChild(buttonA);

		buttonB = Sprite::createWithSpriteFrameName("button_b_normal@2x.png");
		buttonB->setPosition(width - 150, 70);
		buttonB->setScale(0.5);
		buttonB->setOpacity(180);
		_pad->addChild(buttonB);

		listenerKey->onKeyPressed = [=](EventKeyboard::KeyCode key, Event* event){
			dpad->setVisible(false);
			buttonA->setVisible(false);
			buttonB->setVisible(false);
			switch (key)
			{
			case KEY(UP_ARROW):
			case KEY(W):
				KeyPressed[UP] = true;
				if (KeyPressed[RIGHT]){
					KeyPressed[UPRIGHT] = true;
				}
				else if (KeyPressed[LEFT]){
					KeyPressed[UPLEFT] = true;
				}
				break;
			case KEY(DOWN_ARROW):
			case KEY(S):
				KeyPressed[DOWN] = true; 
				if (KeyPressed[RIGHT]){
					KeyPressed[DOWNRIGHT] = true;
				}
				else if (KeyPressed[LEFT]){
					KeyPressed[DOWNLEFT] = true;
				}
				break;
			case KEY(LEFT_ARROW):
			case KEY(A):
				KeyPressed[LEFT] = true;
				if (KeyPressed[UP]){
					KeyPressed[UPLEFT] = true;
				}
				else if (KeyPressed[DOWN]){
					KeyPressed[DOWNLEFT] = true;
				}
				break;
			case KEY(RIGHT_ARROW):
			case KEY(D):
				KeyPressed[RIGHT] = true;
				if (KeyPressed[UP]){
					KeyPressed[UPRIGHT] = true;
				}
				else if (KeyPressed[DOWN]){
					KeyPressed[DOWN] = true;
				}
				break;
			case KEY(J):
				buttonA->setSpriteFrame("button_a_selected@2x.png");
				break;
			case KEY(K):
				buttonB->setSpriteFrame("button_b_selected@2x.png");
				_delegator->onAttack();
				break;
			default:
				break;
			}
		};

		listenerKey->onKeyReleased = [=](EventKeyboard::KeyCode key, Event* event){
			
			switch (key)
			{
			case EventKeyboard::KeyCode::KEY_W:
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				KeyPressed[UP] = false;
				KeyPressed[UPLEFT] = false;
				KeyPressed[UPRIGHT] = false;
				break;
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				KeyPressed[DOWN] = false;
				KeyPressed[DOWNLEFT] = false;
				KeyPressed[DOWNRIGHT] = false;
				break;
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				KeyPressed[LEFT] = false;
				KeyPressed[UPLEFT] = false;
				KeyPressed[DOWNLEFT] = false;
				break;
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				KeyPressed[RIGHT] = false;
				KeyPressed[UPRIGHT] = false;
				KeyPressed[DOWNRIGHT] = false;
				break;
			case EventKeyboard::KeyCode::KEY_J:
				buttonA->setSpriteFrame("button_a_normal@2x.png");
				return;
			case EventKeyboard::KeyCode::KEY_K:
				buttonB->setSpriteFrame("button_b_normal@2x.png");
				return;
			default:
				break;
			}
			dpad->setSpriteFrame("dpad_center@2x.png");
			int SumOfKeyPressed = 0;
			for (int i = 0; i < 8; i++){
				SumOfKeyPressed += KeyPressed[i];
			}
			if (!SumOfKeyPressed){
				this->_delegator->onStop();
				return;
			}
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

		auto listener1 = EventListenerTouchAllAtOnce::create();

		listener1->onTouchesBegan = [=](std::vector<Touch*> touch, Event* event){

			dpad->setVisible(true);
			buttonA->setVisible(true);
			buttonB->setVisible(true);

			auto target = static_cast<Sprite*>(event->getCurrentTarget());

			for (Touch* t : touch){
				Point p = t->getLocation();
				if (p.x < 200){
					dpad->setPosition(p);
				}
				if (p.x >= width - 200 && p.x < width - 100){
					buttonB->setPosition(p);
					buttonB->setSpriteFrame("button_b_selected@2x.png");
					KeyPressed[B] = true;
				}
				if (p.x > width - 100){
					buttonA->setPosition(p);
					buttonA->setSpriteFrame("button_a_selected@2x.png");
					KeyPressed[A] = true;
				}
				log("Touched location = %f, %f", p.x, p.y);
			}

		};

		listener1->onTouchesMoved = [=](std::vector<Touch*> touch, Event* event){
			for (Touch* t : touch){
				Point s = t->getStartLocation();
				Point l = t->getLocation();
				if (l.x < 200){
					int d = (s.x - l.x) * (s.x - l.x) + (s.y - l.y) * (s.y - l.y);
					if (d < 6400){
						int degrees = (int)(-1 * CC_RADIANS_TO_DEGREES(ccpToAngle(s - l)) + 202.5f);
						//log("degrees = %d", degrees);
						//log("Distance = %d", d);
						log("degrees = %d", degrees);
						selectDirection((degrees / 45) % 8);
					}
				}
			}
		};

		listener1->onTouchesEnded = [=](std::vector<Touch*> touch, Event* event){
			for (Touch* t : touch){
				auto p = t->getLocation();
				if (p.x < 200){
					dpad->setSpriteFrame("dpad_center@2x.png");
				}
				else if (p.x >= width - 200 && p.x < width - 100){
					buttonB->setSpriteFrame("button_b_normal@2x.png");
				}
				else if (p.x >= width - 100)
				{
					buttonA->setSpriteFrame("button_a_normal@2x.png");
				}
			}

		};

		auto listener2 = listener1->clone();
		auto listener3 = listener1->clone();
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, dpad);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, buttonA);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, buttonB);

		this->scheduleUpdate();

		ret = true;
	} while (0);

	return ret;
}

void OperationLayer::update(float dt){



	if (KeyPressed[B]){
		this->_delegator->onAttack();
		KeyPressed[B] = false;
		return;
	}
	else if (KeyPressed[UPLEFT]){
		selectDirection(UPLEFT);
		this->_delegator->onWalk(Point(-1, 1), 96);
		return;
	}
	else if (KeyPressed[UPRIGHT]){
		this->_delegator->onWalk(Point(1, 1), 96);
		selectDirection(UPRIGHT);
		return;
	}
	else if (KeyPressed[DOWNRIGHT]){
		this->_delegator->onWalk(Point(1, -1), 96);
		selectDirection(DOWNRIGHT);
		return;
	}
	else if (KeyPressed[DOWNLEFT]){
		this->_delegator->onWalk(Point(-1, -1), 96);
		selectDirection(DOWNLEFT);
		return;
	}
	else if (KeyPressed[UP]){
		this->_delegator->onWalk(Point(0, 1), 96);
		selectDirection(UP);
		return;
	}
	else if (KeyPressed[DOWN]){
		this->_delegator->onWalk(Point(0, -1), 96);
		selectDirection(DOWN);
		return;
	}
	else if (KeyPressed[LEFT]){
		this->_delegator->onWalk(Point(-1, 0), 96);
		selectDirection(LEFT);
		return;
	}
	else if (KeyPressed[RIGHT]){
		this->_delegator->onWalk(Point(1, 0), 96);
		selectDirection(RIGHT);
		return;
	}
	else{
		//this->_delegator->onStop();
		//dpad->setSpriteFrame("dpad_center@2x.png");
		//return;
	}
}

void OperationLayer::selectDirection(int degrees){

	switch (degrees)
	{
	case RIGHT:
		dpad->setSpriteFrame("dpad_right@2x.png");
		break;
	case DOWNRIGHT:
		dpad->setSpriteFrame("dpad_downright@2x.png");
		break;
	case DOWN:
		dpad->setSpriteFrame("dpad_down@2x.png");
		break;
	case DOWNLEFT:
		dpad->setSpriteFrame("dpad_downleft@2x.png");
		break;
	case LEFT:
		dpad->setSpriteFrame("dpad_left@2x.png");
		break;
	case UPLEFT:
		dpad->setSpriteFrame("dpad_upleft@2x.png");
		break;
	case UP:
		dpad->setSpriteFrame("dpad_up@2x.png");
		break;
	case UPRIGHT:
		dpad->setSpriteFrame("dpad_upright@2x.png");
		break;
	default:
		break;
	}
}


