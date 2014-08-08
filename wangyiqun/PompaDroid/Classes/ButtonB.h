#ifndef _BUTTON_B_H_
#define _BUTTON_B_H_

#include "cocos2d.h"
#include "Hero.h"

class ButtonB :public cocos2d::Sprite{
public:
	ButtonB();
	~ButtonB();
	bool init();
	CREATE_FUNC(ButtonB);

	CC_SYNTHESIZE(Hero*, m_hero, Hero);

	bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event *unused_event);
	//void onTouchMoved(cocos2d::Touch* touches, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event *unused_event);
};

#endif//_BUTTON_B_H