#pragma once
#include "cocos2d.h"
#include "SimpleDPadSprite.h"

USING_NS_CC;

class HudLayer : public Layer
{
public:
	HudLayer();
	~HudLayer();

	bool init();
	CREATE_FUNC(HudLayer);

	CC_SYNTHESIZE(SimpleDPad*, _dPad, DPad);
	SpriteBatchNode *_dPads;
};
