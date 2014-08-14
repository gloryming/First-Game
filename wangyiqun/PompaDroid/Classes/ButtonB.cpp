#include "ButtonB.h"

USING_NS_CC;

ButtonB::ButtonB(){

}

ButtonB::~ButtonB(){

}

bool ButtonB::init(){
	bool ret = false;
	do {
		CC_BREAK_IF(!this->initWithSpriteFrameName("button_b_normal@2x.png"));

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(ButtonB::onTouchBegan, this);
		//listener->onTouchMoved = CC_CALLBACK_2(ButtonA::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(ButtonB::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		ret = true;
	} while (0);

	return ret;
}

bool ButtonB::onTouchBegan(Touch* touch, Event* event){
	Point location = touch->getLocation();
	//log("%f, %f", touch->getLocation().x, touch->getLocation().y);

	float distanceSQ = ccpDistanceSQ(location, this->getPosition());
	if (distanceSQ <= 32 * 32){
		setSpriteFrame("button_b_selected@2x.png");
		m_hero->jump();
	//	log("B");
		return true;
	}
	return false;
}

void ButtonB::onTouchEnded(Touch* touch, Event* event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setSpriteFrame("button_b_normal@2x.png");
}