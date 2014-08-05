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

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Joypad.plist");
		m_spriteNodes = SpriteBatchNode::create("Joypad.png");
		this->addChild(m_spriteNodes);
		

		m_dPad = DPad::create();
		m_dPad->setPosition((Director::getInstance()->getVisibleOrigin()) + Point(65,65));
		m_dPad->setScale(0.5);
		m_dPad->setOpacity(100);
		m_spriteNodes->addChild(m_dPad);

		ret = true;
	} while (0);
	return ret;
}