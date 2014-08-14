#include "ButtonA.h"

USING_NS_CC;

ButtonA::ButtonA(){

}

ButtonA::~ButtonA(){

}

bool ButtonA::init(){
	bool ret = false;
	do {
		CC_BREAK_IF(!this->initWithSpriteFrameName("button_a_normal@2x.png"));

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(ButtonA::onTouchBegan, this);
		//listener->onTouchMoved = CC_CALLBACK_2(ButtonA::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(ButtonA::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		ret = true;
	} while (0);

	return ret;
}

bool ButtonA::onTouchBegan(Touch* touch, Event* event){
	Point location = touch->getLocation();
	//log("%f, %f", touch->getLocation().x, touch->getLocation().y);

	float distanceSQ = ccpDistanceSQ(location, this->getPosition());
	if (distanceSQ <= 32 * 32 ){
		setSpriteFrame("button_a_selected@2x.png");
		m_hero->attack();
	//	log("A");
		return true;
	}
	return false;
}

void ButtonA::onTouchEnded(Touch* touch, Event* event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setSpriteFrame("button_a_normal@2x.png");
}