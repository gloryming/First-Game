#ifndef _DPAD_H_
#define _DPAD_H_

#include "cocos2d.h"
#include "Hero.h"

class DPad :public cocos2d::Sprite
{
public :
	DPad();
	~DPad();

	bool init();
	CREATE_FUNC(DPad);

	//void onEnterTransitionDidFinish();
	//void onExit();
	void update(float dt);

	bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch* touches, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event *unused_event);

	void updateDirectionFromTouchLocation(cocos2d::Point loc);

	CC_SYNTHESIZE(bool, m_isHeld, IsHeld);
	CC_SYNTHESIZE(Hero*, m_hero, Hero);


protected:
	float m_radius;
	cocos2d::Point  m_direction;
};

#endif//_DPAD_H_