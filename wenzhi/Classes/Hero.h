#pragma once

#include "cocos2d.h"
#include "ActionSprite.h"

USING_NS_CC;

class Hero : public ActionSprite
{
public:
	Hero();
	~Hero();

	bool init();
	CREATE_FUNC(Hero);

	void walk(Direction dir);
	void stop();
	/*void walk(Direction dir);
	void stop();*/
};