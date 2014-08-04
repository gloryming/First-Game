#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include "Character.h"
class Hero : public Character
{
public:
	Hero();
	~Hero();
	bool init();
	CREATE_FUNC(Hero);

	std::function<void(cocos2d::Point, float)> walk;
	std::function<void(void)> stop;

};

#endif//_HERO_H_