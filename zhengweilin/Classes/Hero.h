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
	//create就是新建一个Hero然后初始化，然后返回这个Hero
	CREATE_FUNC(Hero);
	
};

