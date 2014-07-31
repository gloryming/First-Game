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
	_dPad = SimpleDPad::dPadWithFile(__String::create("pd_dpad.png"), 64);
	_dPad->setPosition(ccp(64.0, 64.0));
	_dPad->setOpacity(100);
	this->addChild(_dPad);

	return true;
}