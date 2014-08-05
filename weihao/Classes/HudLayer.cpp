#include "HudLayer.h"
#include "SimpleDPadSprite.h"

HudLayer::HudLayer()
{
	this->setDPad(NULL);
}

HudLayer::~HudLayer()
{

}

bool HudLayer::init()
{
	if (!Layer::init())
		return false;
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("dPad.plist");
	_dPads = SpriteBatchNode::create("dPad.pvr.ccz");
	_dPads->getTexture()->setAliasTexParameters();
	this->addChild(_dPads,0);
	_dPad = SimpleDPad::dPadWithSpriteFrameName(__String::create("dpad_center@2x.png"), 64);
	_dPad->setPosition(ccp(64.0, 64.0));
	_dPad->setOpacity(100);
	this->addChild(_dPad);

	return true;
}