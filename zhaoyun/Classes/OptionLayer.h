#ifndef Philon_cocos2dx_PompaDroid_OPTIONLAYER_H_
#define Philon_cocos2dx_PompaDroid_OPTIONLAYER_H_
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

#endif // End of Philon_cocos2dx_PompaDroid_GAMELAYER_H_
