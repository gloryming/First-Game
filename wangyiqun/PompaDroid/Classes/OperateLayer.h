#ifndef _OPERATE_LAYER_H_
#define _OPERATE_LAYER_H_

#include "cocos2d.h"
#include "DPad.h"
#include "ButtonA.h"
#include "ButtonB.h"

class OperateLayer :public cocos2d::Layer
{
public:
	OperateLayer();
	~OperateLayer();
	bool init();
	CREATE_FUNC(OperateLayer);

	CC_SYNTHESIZE(DPad*, m_dPad,DPad);
	CC_SYNTHESIZE(ButtonA*, m_buttonA, ButtonA);
	CC_SYNTHESIZE(ButtonB*, m_buttonB, ButtonB);


	cocos2d::SpriteBatchNode* m_spriteNodes;
	void  setHero(Hero* hr){//bridge
		m_dPad->setHero(hr);
	}
	void aSetHero(Hero* hr){
		m_buttonA->setHero(hr);
	}
	void bSetHero(Hero* hr){
		m_buttonB->setHero(hr);
	}
};

#endif//_OPERATE_LAYER_H_