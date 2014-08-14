#ifndef _BUTTON_A_H_
#define _BUTTON_A_H_

#include "cocos2d.h"
#include "Hero.h"

class ButtonA :public cocos2d::Sprite{
public:
	ButtonA();
	~ButtonA();
	bool init();
	CREATE_FUNC(ButtonA);

	CC_SYNTHESIZE(Hero*, m_hero, Hero);

	bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event *unused_event);
	//void onTouchMoved(cocos2d::Touch* touches, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event *unused_event);

};

#endif//_BUTTON_A_H