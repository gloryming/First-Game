#ifndef __OPERATELAYER_H__
#define __OPERATELAYER_H__

#include "cocos2d.h"
#include "Play.h"
#include "HeroLayer.h"
USING_NS_CC;


class OperateLayer : public cocos2d::Layer
{
public:
	OperateLayer(void);
	~OperateLayer(void);

	virtual bool init();

	CREATE_FUNC(OperateLayer);

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	Point o;
    bool pressdown;
	CC_SYNTHESIZE(HeroLayer*, m_pHero, HeroLayer);
private:
/*	void showJoystick(cocos2d::Point pos);
	void hideJoystick();
	void updateJoystick(cocos2d::Point direction, float distance);*/
	cocos2d::Sprite *button;
	cocos2d::Sprite *m_pJoystickBg;
};
#endif //__OPERATELAYER_H__