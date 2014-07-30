#pragma once
#include "cocos2d.h"
#include "ActionSprite.h"

using namespace cocos2d;

class Hero : public ActionSprite
{
public:
	Hero();
	~Hero();

	bool init();
	CREATE_FUNC(Hero);
	
};

