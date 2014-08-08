#pragma once

#include "cocos2d.h"
#include "SimpleDPadSprite.h"
USING_NS_CC;


class OptionLayer : public Layer
{
public:
    OptionLayer();
    ~OptionLayer();

	bool init();
	CREATE_FUNC(OptionLayer);

	CC_SYNTHESIZE(SimpleDPad*, _dPad, DPad);
	SpriteBatchNode *_dPads;
};