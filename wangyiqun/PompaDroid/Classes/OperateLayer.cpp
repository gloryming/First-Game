#include "OperateLayer.h"

USING_NS_CC;

OperateLayer::OperateLayer(){

}

OperateLayer::~OperateLayer(){

}

bool OperateLayer::init(){
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());

		//auto visibleSize = Director::getInstance()->getVisibleSize();
		//this->m_origin = Director::getInstance()->getVisibleOrigin();
		//this->m_screenWidth = visibleSize.width;
		//this->m_screenHeight = visibleSize.height;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Joypad.plist");
		m_spriteNodes = SpriteBatchNode::create("Joypad.png");
		this->addChild(m_spriteNodes);

		m_dPad = DPad::create();
		m_dPad->setPosition(origin + Point(65,65));
		m_dPad->setScale(0.5);
		m_dPad->setOpacity(100);
		m_spriteNodes->addChild(m_dPad);
		
		//
		m_buttonA = ButtonA::create();
		m_buttonA->setPosition(Point(origin.x + visibleSize.width - m_buttonA->getContentSize().width * 0.75,origin.y + m_buttonA->getContentSize().height / 3 ));
		m_buttonA->setScale(0.5);
		m_buttonA->setOpacity(100);
		m_spriteNodes->addChild(m_buttonA);


		m_buttonB = ButtonB::create();
		m_buttonB->setPosition(Point(origin.x + visibleSize.width - m_buttonB->getContentSize().width / 3, origin.y + m_buttonB->getContentSize().height * 0.75));
		m_buttonB->setScale(0.5);
		m_buttonB->setOpacity(100);
		m_spriteNodes->addChild(m_buttonB);

		ret = true;
	} while (0);
	return ret;
}
