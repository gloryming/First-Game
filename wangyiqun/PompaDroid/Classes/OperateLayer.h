#ifndef _OPERATE_LAYER_H_
#define _OPERATE_LAYER_H_

#include "cocos2d.h"
#include "DPad.h"

class OperateLayer :public cocos2d::Layer
{
public:
	OperateLayer();
	~OperateLayer();
	bool init();
	CREATE_FUNC(OperateLayer);

	CC_SYNTHESIZE(DPad*, m_dPad,DPad);
	cocos2d::SpriteBatchNode* m_spriteNodes;
	void  setHero(Hero* hr){
		m_dPad->setHero(hr);
	}
};

#endif//_OPERATE_LAYER_H_